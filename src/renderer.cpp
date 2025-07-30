#include "renderer.hpp"
#include "geometry.hpp"
#include "shader.hpp"
#include "tgaImage.hpp"
#include <algorithm>
#include <cmath>
#include <sstream>
#include <vector>

#define PI 3.14159265358979323846

Renderer::Renderer(int width, int height, Model &model) : model(model) {
  _width = width;
  _height = height;
  image = TGAImage(width, height, TGAImage::RGBA);

  zBuffer =
      TGAImage(width, height, TGAImage::GRAYSCALE);
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      zBuffer.set(x, y, TGAColor(255, 1));
    }
  }
}

Renderer::~Renderer() {}

void Renderer::init() {
  image.clear();
  for (int x = 0; x < _width; x++) {
    for (int y = 0; y < _height; y++) {
      zBuffer.set(x, y, TGAColor(255, 1));
    }
  }
}

TGAImage Renderer::render(Vec3f eye, Vec3f target, Vec3f up, bool wireframe) {
  // Matrix44f CamToWrold({
  //   1,  0,  0,  0,
  //   0,  1,  0,  1,
  //   0,  0,  1,  2,
  //   0,  0,  0,  1
  // });
  // Matrix44f CamToWrold({
  //   //right_x,  up_x,   forward_x,  t_x
  //   1,          0,      0,          0,
  //   //right_y,  up_y,   forward_y,  t_y
  //   0,          0.707,  0.707,      2,
  //   //right_z,  up_z,   forward_z,  t_z
  //   0,          -0.707, 0.707,      2,
  //   0,          0,      0,          1
  // });

  // float angle = -90;
  // float radians = PI / 180 * angle;
  // Matrix44f CamToWrold =
  //     lookAt(3.f * Vec3f({std::cos(radians), 0, -std::sin(radians)}), Vec3f({0, 0, 0}), Vec3f({0, 1, 0}));

  Matrix44f CamToWrold = lookAt(eye, target, up);
  // float n = 1, f = 3, t = 1, b = -1, l = -1, r = 1;
  float n = 1, f = 30, t = 1, b = -1, l = -1, r = 1;
  const int width = this->image.get_width();
  const int height = this->image.get_height();

  Matrix44f View = CamToWrold.inverse();
  Matrix44f Project =
      Matrix44f({2 * n / (r - l), 0, (r + l) / (r - l), 0, 0, 2 * n / (t - b),
                 (t + b) / (t - b), 0, 0, 0, -(f + n) / (f - n),
                 -2 * f * n / (f - n), 0, 0, -1, 0});
  Matrix44f ViewPort =
      Matrix44f({width / 2.f, 0, 0, width / 2.f, 0, height / 2.f, 0,
                 height / 2.f, 0, 0, 255 / 2., 255 / 2., 0, 0, 0, 1});

  // Vec3f lightDir({1, -1, 1});
  Vec3f lightDir((eye - target).normalize());

  init(); // clear image and reset zBuffer
  for (int faceIdx = 0; faceIdx < model.nfaces(); faceIdx++) {
    std::vector<int> face = model.face(faceIdx);
    Vec4f v0 = embed<4>(model.vert(face[0]));
    Vec4f v1 = embed<4>(model.vert(face[1]));
    Vec4f v2 = embed<4>(model.vert(face[2]));

    SimpleShader shader;
    v0 = shader.vertex(v0, View, Project, ViewPort);
    v1 = shader.vertex(v1, View, Project, ViewPort);
    v2 = shader.vertex(v2, View, Project, ViewPort);

    if (wireframe) {
      line(image, v0.x(), v0.y(), v1.x(), v1.y());
      line(image, v1.x(), v1.y(), v2.x(), v2.y());
      line(image, v2.x(), v2.y(), v0.x(), v0.y());
      continue;
    }

    Vec3f vt0 = model.textureVert(face[3]);
    Vec3f vt1 = model.textureVert(face[4]);
    Vec3f vt2 = model.textureVert(face[5]);

    Vec3f nt0 = model.normalVert(face[6]);
    Vec3f nt1 = model.normalVert(face[7]);
    Vec3f nt2 = model.normalVert(face[8]);

    TGAColor c0 = model.textureColor(vt0.x() * model.textureWidth,
                                     (1 - vt0.y()) * model.textureHeight);
    TGAColor c1 = model.textureColor(vt1.x() * model.textureWidth,
                                     (1 - vt1.y()) * model.textureHeight);
    TGAColor c2 = model.textureColor(vt2.x() * model.textureWidth,
                                     (1 - vt2.y()) * model.textureHeight);

    float ity0 = nt0 * lightDir + 0.4;
    float ity1 = nt1 * lightDir + 0.4;
    float ity2 = nt2 * lightDir + 0.4;

    int minX = std::max(0.0f, std::min({v0.x(), v1.x(), v2.x()}));
    int maxX = std::min(width, (int)std::max({v0.x(), v1.x(), v2.x()}));
    int minY = std::max(0.0f, std::min({v0.y(), v1.y(), v2.y()}));
    int maxY = std::min(height, (int)std::max({v0.y(), v1.y(), v2.y()}));

    float area = edgeFunction(v0, v1, v2);
    for (int x = minX; x <= maxX; x++) {
      for (int y = minY; y <= maxY; y++) {
        Vec4f p({(float)x, (float)y});
        if (inside(v0, v1, v2, p)) {
          float w0 = edgeFunction(v1, v2, p) / area;
          float w1 = edgeFunction(v2, v0, p) / area;
          float w2 = edgeFunction(v0, v1, p) / area;
          // 1/z = w0/z0 + w1/z1 + w2/z2
          float z = 1.0 / (w0 / v0.z() + w1 / v1.z() + w2 / v2.z());

          // std::cout << "z: " << z << std::endl;
          if (abs(z) < zBuffer.get(x, y).val) {
            // std::cout << "p: " << p << std::endl;
            zBuffer.set(x, y, TGAColor(abs(z), 1));
            TGAColor color = shader.fragment(v0, v1, v2, p, c0, c1, c2, ity0, ity1, ity2);
            image.set(x, y, color);
          }
        }
      }
    }
  }
  return image;
}

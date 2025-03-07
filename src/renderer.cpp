#include "renderer.hpp"
#include "geometry.hpp"
#include "shader.hpp"
#include <vector>

Renderer::Renderer(TGAImage &image, Model &model) : image(image), model(model) {
  zBuffer = TGAImage(image.get_width(), image.get_height(), TGAImage::GRAYSCALE);
  for (int x = 0; x < image.get_width(); x++) {
    for (int y = 0; y < image.get_height(); y++) {
      zBuffer.set(x,  y, TGAColor(255, 1));
    }
  }
}

Renderer::~Renderer() {}

int Renderer::render() {
  Matrix44f CamToWrold({
    1,  0,  0,  0,
    0,  1,  0,  0,
    0,  0,  1,  3,
    0,  0,  0,  1
  });

  float n = 1, f = 3, t = 1, b = -1, l = -1, r = 1;
  const int width = this->image.get_width();
  const int height = this->image.get_height();

  Matrix44f View = CamToWrold.inverse();
  Matrix44f Project = Matrix44f({
    2*n/(r-l),    0,            (r+l)/(r-l),  0,
    0,            2*n/(t-b),    (t+b)/(t-b),  0,
    0,            0,            -(f+n)/(f-n), -2*f*n/(f-n),
    0,            0,            -1,           0
  });
  Matrix44f ViewPort = Matrix44f({
    width/2.f,   0,          0,     width/2.f,
    0,          height/2.f,  0,      height/2.f,
    0,          0,          255/2., 255/2.,
    0,          0,          0,      1
  });

  for (int faceIdx = 0; faceIdx < model.nfaces(); faceIdx++) {
    std::vector<int> face = model.face(faceIdx);
    Vec4f v0 = embed<4>(model.vert(face[0]));
    Vec4f v1 = embed<4>(model.vert(face[1]));
    Vec4f v2 = embed<4>(model.vert(face[2]));

    SimpleShader shader;
    v0 = shader.vertex(v0, View, Project, ViewPort);
    v1 = shader.vertex(v1, View, Project, ViewPort);
    v2 = shader.vertex(v2, View, Project, ViewPort);

    line(image, v0[0], v0[1], v1[0], v1[1]);
    line(image, v1[0], v1[1], v2[0], v2[1]);
    line(image, v2[0], v2[1], v0[0], v0[1]);
  }
  return 0;
}

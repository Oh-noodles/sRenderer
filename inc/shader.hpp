#include "tgaImage.hpp"
#ifndef __SHADER_H__
#include "geometry.hpp"

struct IShader {
  virtual Vec4f vertex(Vec4f, Matrix44f View, Matrix44f Project, Matrix44f ViewPort) = 0;
  virtual TGAColor fragment(Vec4f v0, Vec4f v1, Vec4f v2, Vec4f p, TGAColor c0, TGAColor c1, TGAColor c2, float ity0, float ity1, float ity2) = 0;
};


struct SimpleShader: public IShader {
  Vec4f vertex(Vec4f v, Matrix44f View, Matrix44f Project, Matrix44f ViewPort) {
    v = ViewPort * Project * View * v;
    for (int i = 0; i < 3; i++) {
      v[i] /= v[3];
    }
    return v;
  };
  TGAColor fragment(Vec4f v0, Vec4f v1, Vec4f v2, Vec4f p, TGAColor c0, TGAColor c1, TGAColor c2, float ity0, float ity1, float ity2) {
    float area = edgeFunction(v0, v1, v2);
    float w0 = edgeFunction(v1, v2, p) / area;
    float w1 = edgeFunction(v2, v0, p) / area;
    float w2 = edgeFunction(v0, v1, p) / area;
    // 1/z = w0/z0 + w1/z1 + w2/z2
    float z = 1.0 / (w0/v0.z() + w1/v1.z() + w2/v2.z());
    // c * 1/z = (c0 * w0/z0 + c1 * w1/z1 + c2 * w2/z2)
    float r = z * (c0.r * w0/v0.z() + c1.r * w1/v1.z() + c2.r * w2/v2.z());
    float g = z * (c0.g * w0/v0.z() + c1.g * w1/v1.z() + c2.g * w2/v2.z());
    float b = z * (c0.b * w0/v0.z() + c1.b * w1/v1.z() + c2.b * w2/v2.z());

    // std::cout << "r0: " << c0.r << ", g0: " << c0.g << ", b0: " << c0.b << std::endl;
    // std::cout << "r: " << r << ", g: " << g << ", b: " << b << std::endl;
    // ity * 1/z = (ity0 * w0/z0 + ity1 * w1/z1 + iyt2 * w2/z2)
    float ity = z * (ity0 * w0/v0.z() + ity1 * w1/v1.z() + ity2 * w2/v2.z());
    ity = std::min(ity, 1.0f);
    ity = std::max(ity, 0.0f);
    // ity = 1.0f;
    return TGAColor(b*ity, g*ity, r*ity, 255*ity);
  };
};

int line(TGAImage &image, float x1, float x2, float y1, float y2);
int line(TGAImage &image, int x1, int y1, int x2, int y2);

#endif

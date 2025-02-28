#include "tgaImage.hpp"
#ifndef __SHADER_H__
#include "geometry.hpp"

struct IShader {
  virtual Vec4f vertex(Vec4f, Matrix44f View, Matrix44f Project, Matrix44f ViewPort) = 0;
  virtual int fragment(Vec4f v0, Vec4f v1, Vec4f v2, Vec4f p) = 0;
};


struct SimpleShader: IShader {
  Vec4f vertex(Vec4f v, Matrix44f View, Matrix44f Project, Matrix44f ViewPort) {
    v = ViewPort * Project * View * v;
    for (int i = 0; i < 3; i++) {
      v[i] /= v[3];
    }
    return v;
  };
  int fragment(Vec4f v0, Vec4f v1, Vec4f v2, Vec4f p) {
    return 0;
  };
};

int line(TGAImage &image, float x1, float x2, float y1, float y2);
int line(TGAImage &image, int x1, int y1, int x2, int y2);

#endif

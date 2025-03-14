#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "geometry.hpp"
#include "model.hpp"
#include "tgaImage.hpp"

class Renderer {
  public:
    TGAImage &image;
    Model &model;
    TGAImage zBuffer;
    Matrix44f View, Project, ViewPort;

    Renderer(TGAImage &image, Model &model);
    ~Renderer();
    int render(bool wireframe = false);
};

#endif

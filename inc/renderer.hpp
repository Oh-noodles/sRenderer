#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "geometry.hpp"
#include "model.hpp"
#include "tgaImage.hpp"

class Renderer {
  public:
    TGAImage image;
    Model &model;
    TGAImage zBuffer;
    Matrix44f View, Project, ViewPort;

    Renderer(int width, int height, Model &model);
    ~Renderer();
    TGAImage render(Vec3f eye, Vec3f target, Vec3f up, bool wireframe = false);
};

#endif

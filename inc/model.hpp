#ifndef __MODEL_H__
#define __MODEL_H__

#include "geometry.hpp"
#include "tgaImage.hpp"
#include <vector>

class Model {
private:
  std::vector<Vec3f> _verts;
  std::vector<std::vector<int>> _faces;
  std::vector<Vec3f> _textureVerts;
  std::vector<Vec3f> _normalVerts;
  TGAImage _textureImage;

public:
  int textureWidth = 0;
  int textureHeight = 0;
  Model();
  Model(const char *objFilename, const char *textureFilename = "");
  ~Model();
  int nverts();
  int nfaces();
  int nTextureVerts();
  int nNormalVerts();
  Vec3f vert(int i);
  Vec3f textureVert(int i);
  Vec3f normalVert(int i);
  std::vector<int> face(int i);
  TGAColor textureColor(int x, int y);
};

#endif

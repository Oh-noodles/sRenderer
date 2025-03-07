#ifndef __MODEL_H__
#define __MODEL_H__

#include "geometry.hpp"

class Model {
private:
  std::vector<Vec3f> _verts;
  std::vector<std::vector<int>> _faces;

public:
  Model();
  Model(const char *filename);
  ~Model();
  int nverts();
  int nfaces();
  Vec3f vert(int i);
  std::vector<int> face(int i);
};

#endif

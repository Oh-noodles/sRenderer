#include "model.hpp"
#include "geometry.hpp"
#include "tgaImage.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

Model::Model(const char *objFilename, const char *textureFilename) {
  std::ifstream in;
  in.open(objFilename, std::ifstream::in);
  if (in.fail())
    return;

  _textureImage = TGAImage();
  _textureImage.read_tga_file(textureFilename);
  textureWidth = _textureImage.get_width();
  textureHeight = _textureImage.get_height();
  std::cout << "textureWidth: " << textureWidth << std::endl;
  std::cout << "textureHeight: " << textureHeight << std::endl;


  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    if (!line.compare(0, 2, "v ")) {
      // vertex
      char cTrash;
      float x, y, z;
      iss >> cTrash >> x >> y >> z;
      _verts.push_back(Vec3f({x, y, z}));
    } else if (!line.compare(0, 3, "vt ")) {
      // textural vertex
      std::string sTrash;
      float x, y, z;
      iss >> sTrash >> x >> y >> z;
      _textureVerts.push_back(Vec3f({x, y, z}));
    } else if (!line.compare(0, 3, "vn ")) {
      // normal vertext 
      std::string sTrash;
      float x, y, z;
      iss >> sTrash >> x >> y >> z;
      _normalVerts.push_back(Vec3f({x, y, z}));
    } else if (!line.compare(0, 2, "f ")) {
      // face
      char cTrash;
      int v0, v1, v2, vt0, vt1, vt2, nt0, nt1, nt2;
      iss >> cTrash;
      iss >> v0 >> cTrash >> vt0 >> cTrash >> nt0;
      iss >> v1 >> cTrash >> vt1 >> cTrash >> nt1;
      iss >> v2 >> cTrash >> vt2 >> cTrash >> nt2;
      if (iss.eof()) {
        _faces.push_back(std::vector<int>({v0-1, v1-1, v2-1, vt0-1, vt1-1, vt2-1, nt0-1, nt1-1, nt2-1}));
      } else {
        int v3, vt3, nt3;
        iss >> v3 >> cTrash >> vt3 >> cTrash >> nt3;
        _faces.push_back(std::vector<int>({v0-1, v1-1, v3-1, vt0-1, vt1-1, vt3-1, nt0-1, nt1-1, nt3-1}));
        _faces.push_back(std::vector<int>({v3-1, v1-1, v2-1, vt3-1, vt1-1, vt2-1, nt3-1, nt1-1, nt2-1}));
      }
    }
  }


}

Model::~Model() {}

Vec3f Model::vert(int i) { return _verts[i]; }

Vec3f Model::textureVert(int i) { return _textureVerts[i]; }

Vec3f Model::normalVert(int i) { return _normalVerts[i]; }

std::vector<int> Model::face(int i) { return _faces[i]; }

int Model::nverts() { return _verts.size(); }

int Model::nTextureVerts() { return _textureVerts.size(); }

int Model::nNormalVerts() { return _normalVerts.size(); }

int Model::nfaces() { return _faces.size(); }

TGAColor Model::textureColor(int x, int y) {
  return _textureImage.get(x, y);
}

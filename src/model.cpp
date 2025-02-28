#include "model.hpp"
#include <fstream>
#include <sstream>
#include <vector>

Model::Model(const char *filename) {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;

    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        if (!line.compare(0, 2, "v ")) {
            // vertex
            char cTrash;
            float x, y, z;
            iss >> cTrash >> x >> y >> z;
            Vec3f v;
            _verts.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            // face
            char cTrash;
            int v0, v1, v2, iTrash;
            iss >> cTrash >> v0 >> cTrash >> iTrash >> cTrash >> iTrash;
            iss >> cTrash >> v1 >> cTrash >> iTrash >> cTrash >> iTrash;
            iss >> cTrash >> v2 >> cTrash >> iTrash >> cTrash >> iTrash;
            _faces.push_back(std::vector<int>({v0, v1, v2}));
        }
    }
}

Model::~Model() {}

Vec3f Model::vert(int i) {
    return _verts[i];
}

std::vector<int> Model::face(int i) {
    return _faces[i];
} 

int Model::nverts() {
    return _verts.size();
}

int Model::nfaces() {
    return _faces.size();
}

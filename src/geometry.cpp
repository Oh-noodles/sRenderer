#include "geometry.hpp"
#include <array>

Matrix44f::Matrix44f() {}
Matrix44f::~Matrix44f() {}
Matrix44f::Matrix44f(float m[16]) {
    for (int i = 0; i < 16; i++)
      data[i] = m[i];
}

Matrix44f::Matrix44f(std::array<float, 16> m) {
  for (int i = 0; i < 16; i++)
    data[i] = m[i];
}

Matrix44f Matrix44f::inverse() {
    float m[16];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            m[i*4+j] = this->data[i*4+j] * (i==j ? 1 : -1);
        }
    return Matrix44f(m);
}

Matrix44f Matrix44f::transpose() {
    float m[16] = {};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            m[j*4+i] = this->data[i*4+j];
        }
    return Matrix44f(m);
}

Matrix44f operator*(Matrix44f mat1, Matrix44f mat2) {
    float m[16] = {};
    // every row of m1
    for (int m1i = 0; m1i < 4; m1i++) {
        // every col of m2
        for (int m2j = 0; m2j < 4; m2j++) {
            float val = 0;
            for (int k = 0; k < 4; k++) {
                val += mat1.data[m1i * 4 + k] * mat2.data[k * 4 + m2j];
            }
            m[m1i * 4 + m2j] = val;
        }
    }
    return Matrix44f(m);
}

Vec4f operator*(Matrix44f mat, Vec4f v) {
  Vec4f t;
  for (int i = 0; i < 4; i++) {
    float val = 0;
    for (int j = 0; j < 4; j++) {
      val += mat.data[i * 4 + j] * v[j];
    }
    t[i] = val;
  }
  return t;
}

std::ostream& operator<<(std::ostream &s, Matrix44f m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            s << m.data[i * 4 + j] << "\t";
        }
        s << "\n";
    }
    return s;
}

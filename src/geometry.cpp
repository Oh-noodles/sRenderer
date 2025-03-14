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
    Matrix44f mat;
    float inv[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            inv[j*4+i] = invf(i, j, this->data);
        }
    }
    double D = 0;
    for (int k = 0; k < 4; k++) {
        D += this->data[k] * inv[k * 4];
    }
    if (D == 0) {
        std::cout << "D == 0" << std::endl;
        return mat;
    }
    D = 1.0 / D;
    for (int i = 0; i < 16; i++) {
        mat.data[i] = inv[i] * D;
    }
    return mat;
}


Matrix44f Matrix44f::transpose() {
    float m[16] = {};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            m[j*4+i] = this->data[i*4+j];
        }
    return Matrix44f(m);
}


Matrix44f lookAt(Vec3f eye, Vec3f center, Vec3f up) {
  Vec3f forward = (eye - center).normalize();
  Vec3f right = cross(up, forward).normalize();
  up.normalize();
  return Matrix44f({
    right.x(), up.x(), forward.x(), eye.x(),
    right.y(), up.y(), forward.y(), eye.y(),
    right.z(), up.z(), forward.z(), eye.z(),
    0,         0,      0,           1
  });
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

float invf(int i,int j,const float* m){

    int o = 2+(j-i);

    i += 4+o;
    j += 4-o;

    #define e(a,b) m[ ((j+b)%4)*4 + ((i+a)%4) ]

    float inv =
     + e(+1,-1)*e(+0,+0)*e(-1,+1)
     + e(+1,+1)*e(+0,-1)*e(-1,+0)
     + e(-1,-1)*e(+1,+0)*e(+0,+1)
     - e(-1,-1)*e(+0,+0)*e(+1,+1)
     - e(-1,+1)*e(+0,-1)*e(+1,+0)
     - e(+1,-1)*e(-1,+0)*e(+0,+1);

    return (o%2)?inv : -inv;

    #undef e

}

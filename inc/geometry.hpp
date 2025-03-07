#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include <array>
#include <iostream>

template <typename T, int DIM> struct Vec {
private:
  T _data[DIM];
  T get(int i) { return i < DIM ? _data[i] : T(); }
  T set(int i, T val) {
    if (i < DIM) {
      _data[i] = val;
    }
  }

public:
  Vec() {
    for (int i = 0; i < DIM; i++) {
      _data[i] = T();
    }
  }
  Vec(T d[DIM]) {
    for (int i = 0; i < DIM; i++) {
      _data[i] = d[i];
    }
  }
  Vec(std::array<T, DIM> d) {
    for (int i = 0; i < DIM; i++) {
      _data[i] = d[i];
    }
  }
  T &operator[](int i) {
    return _data[i];
  }
  T x() { return get(0); }
  T y() { return get(1); }
  T z() { return get(2); }
  T w() { return get(3); }
  T x(T val) { return set(0, val); }
  T y(T val) { return set(1, val); }
  T z(T val) { return set(2, val); }
  T w(T val) { return set(3, val); }
};

typedef Vec<float, 3> Vec3f;
typedef Vec<float, 4> Vec4f;

template <typename T, int DIM>
std::ostream &operator<<(std::ostream &s, Vec<T, DIM> v) {
  s << "(" << v[0];
  for (int i = 1; i < DIM; i++) {
    s << ", " << v[i];
  }
  s << ")";
  return s;
}

template <int tDIM, typename T, int sDIM>
Vec<T, tDIM> embed(Vec<T, sDIM> v, T fill = 1) {
  Vec<T, tDIM> t;
  for (int i = 0; i < tDIM; i++) {
    t[i] = i < sDIM ? v[i] : fill;
  }
  return t;
}

class Matrix44f {
private:
public:
  float data[16] = {};
  Matrix44f();
  Matrix44f(std::array<float, 16> m);
  Matrix44f(float m[16]);
  ~Matrix44f();
  Matrix44f inverse();
  Matrix44f transpose();
};

Matrix44f operator*(Matrix44f mat1, Matrix44f mat2);
Vec4f operator*(Matrix44f mat, Vec4f v);
std::ostream &operator<<(std::ostream &s, Matrix44f mat);
#endif

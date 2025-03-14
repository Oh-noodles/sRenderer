#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include <array>
#include <iostream>
#include <cmath>

template <typename T, int DIM> struct Vec {
private:
  T _data[DIM];
  T get(int i) { return i < DIM ? _data[i] : T(); }
  void set(int i, T val) {
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
  Vec<T, DIM> normalize() {
    float sum = 0;
    for (int i = 0; i < DIM; i++) {
      sum += std::pow(_data[i], 2);
    }
    sum = std::sqrt(sum);
    for (int i = 0; i < DIM; i++) {
      _data[i] /= sum;
    }
    return *this;
  }
  T &operator[](int i) {
    return _data[i];
  }
  T x() { return get(0); }
  T y() { return get(1); }
  T z() { return get(2); }
  T w() { return get(3); }
  T r() { return get(0); }
  T g() { return get(1); }
  T b() { return get(2); }
  T a() { return get(3); }
  void x(T val) { set(0, val); }
  void y(T val) { set(1, val); }
  void z(T val) { set(2, val); }
  void w(T val) { set(3, val); }
  void r(T val) { set(0, val); }
  void g(T val) { set(1, val); }
  void b(T val) { set(2, val); }
  void a(T val) { set(3, val); }
};

typedef Vec<float, 3> Vec3f;
typedef Vec<float, 4> Vec4f;
typedef Vec<float, 2> Vec2f;

template <typename T, int DIM>
std::ostream &operator<<(std::ostream &s, Vec<T, DIM> v) {
  s << "(" << v[0];
  for (int i = 1; i < DIM; i++) {
    s << ", " << v[i];
  }
  s << ")";
  return s;
}

template <typename T, int DIM>
T operator*(Vec<T, DIM> v0, Vec<T, DIM> v1) {
  T ret = T();
  for (int i = 0;i < DIM; i++) {
    ret += v0[i] * v1[i];
  }
  return ret;
}

template <typename T, int DIM>
Vec<T, DIM> operator*(T a, Vec<T, DIM> v) {
  Vec<T, DIM> ret;
  for (int i = 0; i < DIM; i++) {
    ret[i] = a * v[i];
  }
  return ret;
}

template <typename T, int DIM>
Vec<T, DIM> operator-(Vec<T, DIM> v0, Vec<T, DIM> v1) {
  Vec<T, DIM> ret;
  for (int i = 0; i < DIM; i++) {
    ret[i] = v0[i] - v1[i];
  }
  return ret;
}

template <typename T>
Vec<T, 3> cross(Vec<T, 3>v0, Vec<T, 3> v1) {
  Vec<T, 3> ret({
    v0.y()*v1.z() - v0.z()*v1.y(),
    v0.z()*v1.x() - v0.x()*v1.z(),
    v0.x()*v1.y() - v0.y()*v1.x()
  });
  return ret;
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

Matrix44f lookAt(Vec3f eye, Vec3f center, Vec3f up);

template <typename T, int DIM>
float edgeFunction(Vec<T, DIM> v0, Vec<T, DIM> v1, Vec<T, DIM> v2) {
  return (v2.x() - v0.x()) * (v1.y() - v0.y()) - (v2.y() - v0.y()) * (v1.x() - v0.x());
}

template <typename T, int DIM>
bool inside(Vec<T, DIM> v0, Vec<T, DIM> v1, Vec<T, DIM> v2, Vec<T, DIM> p) {
  float w0 = edgeFunction(v1, v2, p);
  float w1 = edgeFunction(v2, v0, p);
  float w2 = edgeFunction(v0, v1, p);
  return (w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0);
}

float invf(int i,int j,const float* m);
#endif

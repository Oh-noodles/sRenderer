#include "shader.hpp"
#include "tgaImage.hpp"
#include <__type_traits/is_swappable.h>
#include <fstream>

int line(TGAImage &image, int x1, int y1, int x2, int y2) {
  bool swaped = false;
  TGAColor color(255, 255, 255, 255);
  image.set(x1, y1, color);
  if (x1 == x2 && y1 == y2) return 0;
  if (x1 == x2) {
    swaped = true;
    std::swap(x1, y1);
    std::swap(x2, y2);
  }
  if (x1 > x2) {
    std::swap(x1, x2);
    std::swap(y1, y2);
  } 

  float k = (float)(y2 - y1) / (x2 - x1);
  float inc = 0;
  int y = y1;
  for (int x = x1; x <= x2; x++) {
    inc += k;
    if (inc >= 1) {
      inc -= k;
      y += 1;
    }
    swaped ? image.set(y, x, color) : image.set(x, y, color);
  }
  return 0;
}

#pragma once

#include <string>
using namespace std;

class ImagePart {
public:
  int x;
  int y;
  int w;
  int h;

  inline ImagePart(int x, int y, int w, int h):
    x(x), y(y), w(w), h(h) {
  };
};

class Frame {
public:
  ImagePart part;
  unsigned int duration;
  
  inline Frame(int x, int y, int w, int h, unsigned int duration):
    part(x, y, w, h), duration(duration) {
  };
};


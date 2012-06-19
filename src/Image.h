#pragma once

#include <string>
using namespace std;

typedef unsigned int ImgId;

class ImagePart {
public:
  ImgId img;
  int x;
  int y;
  int w;
  int h;

  inline ImagePart(ImgId img, int x, int y, int w, int h):
    img(img), x(x), y(y), w(w), h(h) {
  };
};

class Frame {
public:
  ImagePart part;
  unsigned int duration;
  
  inline Frame(ImgId img, int x, int y, int w, int h, unsigned int duration):
    part(img, x, y, w, h), duration(duration) {
  };
};


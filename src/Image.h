#pragma once

#include <string>
using namespace std;

class ImageRect {
public:
  int x;
  int y;
  int w;
  int h;

  inline ImageRect():
    x(-1), y(-1), w(-1), h(-1) {
  };
  inline ImageRect(int x, int y, int w, int h):
    x(x), y(y), w(w), h(h) {
  };
  inline bool isValid() {
    return w != -1;
  }
};

class Frame {
public:
  ImageRect rect;
  unsigned int duration;
  
  inline Frame(int x, int y, int w, int h, unsigned int duration):
    rect(x, y, w, h), duration(duration) {
  };
};

class ImagePart {
public:
  string name;
  ImageRect rect;

  inline ImagePart(string const &name, int x, int y, int w, int h):
    name(name), rect(x, y, w, h) {
  };
  inline ImagePart():
    name(""), rect(-1, -1, -1, -1) {
  };
};


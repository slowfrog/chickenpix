/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
  inline bool isValid() const {
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


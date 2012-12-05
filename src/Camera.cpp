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
 
#include <sstream>
#include "Camera.h"
#include "ComponentRegistry.h"

Component::Type
Camera::TYPE = CAMERA_TYPE;

Camera::Camera():
  Component(Camera::TYPE), offsetX_(0.0f), offsetY_(0.0f), width_(0), height_(0) {
}

Camera::Camera(float offsetX, float offsetY, unsigned int width, unsigned int height):
  Component(Camera::TYPE), offsetX_(offsetX), offsetY_(offsetY), width_(width), height_(height) {
}

Camera::~Camera() {
}

string
Camera::toString() const {
  ostringstream out;
  out << "{Camera offset=" << offsetX_ << "," << offsetY_ <<
    " size=" << width_ << "," << height_ <<  "}" << ends;
  return out.str();
}

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
#include "CL.h"
#include "../BVisual.h"
#include "../Image.h"


class CLVisualImage: public BVisual {
private:
  CL_Image &image_;
  ImageRect rect_;
  
public:
  CLVisualImage(CL_Image &image);
  CLVisualImage(CL_Image &image, ImageRect rect);
  virtual ~CLVisualImage();

  virtual void draw(VisualContext &vc, float x, float y, int delta=-1);
  virtual void debugDraw(VisualContext &vc, float x, float y, int delta,
                         float left, float top, float right, float bottom);
  virtual int getWidth(VisualContext &vc) const;
  virtual int getHeight(VisualContext &vc) const;
  virtual string toString() const;
};

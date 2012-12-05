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
#include "Component.h"
#include "VisualContext.h"

// This class is called BVisual, because Visual is already used in XWindows
class BVisual: public Component {
private:
  float cx_;
  float cy_;
  int zOrder_;
  bool gui_;
  
public:
  static Type TYPE;
  
  BVisual(float cx, float cy, int zOrder=0, bool gui=false);
  BVisual(int zOrder=0, bool gui=false);
  virtual ~BVisual();

  inline
  float getCenterX() const {
    return cx_;
  }
  inline
  void setCenterX(float cx) {
    cx_ = cx;
  }
  inline
  float getCenterY() const {
    return cy_;
  }
  inline
  void setCenterY(float cy) {
    cy_ = cy;
  }
  inline
  void setCenter(float cx, float cy) {
    cx_ = cx;
    cy_ = cy;
  }
  
  inline
  int getZOrder() const {
    return zOrder_;
  }
  inline
  void setZOrder(int zOrder) {
    zOrder_ = zOrder;
  }

  static bool compareZOrder(BVisual const &visual1, BVisual const &visual2);
  
  inline
  bool isGUI() const {
    return gui_;
  }
  inline
  void setGUI(bool gui) {
    gui_ = gui;
  }
  virtual void draw(VisualContext &vc, float x, float y, int delta=-1) = 0;
  virtual void debugDraw(VisualContext &vc, float x, float y, int delta,
                         float left, float top, float right, float bottom) {
    draw(vc, x, y, delta);
  }
  virtual int getWidth(VisualContext &vc) const = 0;
  virtual int getHeight(VisualContext &vc) const = 0;

  virtual inline
  bool isText() const {
    return false;
  }

  virtual string toString() const;
};

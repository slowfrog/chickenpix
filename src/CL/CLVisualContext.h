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
#include "../VisualContext.h"

class CLVisualContext: public VisualContext {
private:
  CL_DisplayWindow &window_;

public:
  CLVisualContext(CL_DisplayWindow &window):
    window_(window) {
  }

  virtual ~CLVisualContext() {}

  inline
  CL_DisplayWindow &getWindow() {
    return window_;
  }
  
  inline
  CL_GraphicContext &getGraphicContext() {
    return window_.get_gc();
  }

  inline
  virtual int getWidth() const {
    return window_.get_geometry().get_width();
  }
  
  inline
  virtual int getHeight() const {
    return window_.get_geometry().get_height();
  }
};

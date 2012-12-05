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

#include "SFML.h"
#include "../VisualContext.h"

class SFMLVisualContext: public VisualContext {
private:
  sf::RenderWindow &rw_;

public:
  SFMLVisualContext(sf::RenderWindow &rw):
    rw_(rw) {
  }

  virtual ~SFMLVisualContext() {}

  inline
  sf::RenderTarget &getRenderTarget() const {
    return rw_;
  }
  
  inline
  sf::RenderWindow &getRenderWindow() const {
    return rw_;
  }

  inline
  virtual int getWidth() const {
    return (int) rw_.GetWidth();
  }

  inline
  virtual int getHeight() const {
    return (int) rw_.GetHeight();
  }
};

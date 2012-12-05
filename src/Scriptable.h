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
#include "Component.h"

class Scriptable: public Component {
private:
  string name_;
  bool initDone_;
  bool exitDone_;
public:
  static Type TYPE;
  Scriptable(string const &name);
  virtual ~Scriptable();

  inline string const &getName() const {
    return name_;
  }
  virtual void update(int now);

  inline bool isInitDone() const {
    return initDone_;
  }
  inline void setInitDone(bool done) {
    initDone_ = done;
  }
  inline bool isExitDone() const {
    return exitDone_;
  }
  inline void setExitDone(bool done) {
    exitDone_ = done;
  }

  virtual string toString() const;
};

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

class Audio: public Component {
private:
  string name_;
  bool   looping_;
  bool   played_;
  // ? Volume
public:
  static Type TYPE;

  Audio(const string &name, bool looping = false);
  virtual ~Audio();

  inline
  virtual bool isConcrete() {
    return false;
  }
  inline
  const string &getName() const {
    return name_;
  }
  inline
  void setName(const string &name) {
    name_ = name; // Should stop playing...
  }
  inline
  bool isLooping() const {
    return looping_;
  }
  inline
  void setLooping(bool looping) {
    looping_ = looping;
  }
  inline
  bool hasPlayed() const {
    return played_;
  }

  inline virtual void play() {
    played_ = true;
  };
  inline virtual bool isPlaying() {
    return false;
  };
  inline virtual void stop() {};
  
  virtual string toString() const;
};

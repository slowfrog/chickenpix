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
#include "../Audio.h"

namespace sf {
  class Sound;
};

class SFMLAudio: public Audio {
private:
  sf::SoundBuffer &buffer_;
  sf::Sound sound_;

public:
  SFMLAudio(const string &name, bool looping, sf::SoundBuffer &buffer);
  virtual ~SFMLAudio();

  inline
  virtual bool isConcrete() {
    return true;
  }
  virtual void play();
  virtual bool isPlaying();
  virtual void stop();
  
  virtual string toString() const;
};

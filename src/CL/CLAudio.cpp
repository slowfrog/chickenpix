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
 
#include "../log.h"
#include "CL.h"
#include "CLAudio.h"

CLAudio::CLAudio(const string &name, bool looping, CL_SoundBuffer &buffer):
  Audio(name, looping), buffer_(buffer), session_(buffer_.prepare()) {
}

CLAudio::~CLAudio() {
}

void
CLAudio::play() {
  if (!isPlaying()) {
    Audio::play();
    session_.set_looping(isLooping());
    session_.play();
  }
}

bool
CLAudio::isPlaying() {
  bool ret = session_.is_playing();
  return ret;
}

void
CLAudio::stop() {
  session_.stop();
}

string
CLAudio::toString() const {
  return "{CLAudio name=" + getName() + "}";
}

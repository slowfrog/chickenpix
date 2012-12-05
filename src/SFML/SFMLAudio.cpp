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
#include "SFML.h"
#include "SFMLAudio.h"

SFMLAudio::SFMLAudio(const string &name, bool looping, sf::SoundBuffer &buffer):
  Audio(name, looping), buffer_(buffer), sound_(buffer) {
}

SFMLAudio::~SFMLAudio() {
}

void
SFMLAudio::play() {
  if (!isPlaying()) {
    LOG2 << "Starting " << getName() << " looping " << isLooping() << "\n";
    Audio::play();
    sound_.SetPlayingOffset(0);
    sound_.SetLoop(isLooping());
    sound_.Play();
  }
}

bool
SFMLAudio::isPlaying() {
  return ((sound_.GetStatus() == sf::Sound::Playing) &&
          !(sound_.GetPlayingOffset() >= buffer_.GetDuration()));
}

void
SFMLAudio::stop() {
  sound_.Stop();
}

string
SFMLAudio::toString() const {
  return "{SFMLAudio name=" + getName() + "}";
}

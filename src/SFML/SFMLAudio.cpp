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

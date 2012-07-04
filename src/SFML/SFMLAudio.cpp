#include "SFML.h"
#include "SFMLAudio.h"

SFMLAudio::SFMLAudio(const string &name, sf::SoundBuffer &buffer):
  Audio(name), buffer_(buffer), sound_(buffer) {
}

SFMLAudio::~SFMLAudio() {
}

void
SFMLAudio::play() {
  sound_.Play();
}

bool
SFMLAudio::isPlaying() {
  return sound_.GetStatus() == sf::Sound::Playing;
}

void
SFMLAudio::stop() {
  sound_.Stop();
}

string
SFMLAudio::toString() const {
  return "{SFMLAudio name=" + getName() + "}";
}

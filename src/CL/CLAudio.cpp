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

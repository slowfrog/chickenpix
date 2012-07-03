#include "CL.h"
#include "CLAudio.h"

CLAudio::CLAudio(CL_SoundBuffer &buffer):
  Audio(), buffer_(buffer), session_(buffer_.prepare()) {
}

CLAudio::~CLAudio() {
}

void
CLAudio::play() {
  session_.play();
}

bool
CLAudio::isPlaying() {
  return session_.is_playing();
}

void
CLAudio::stop() {
  session_.stop();
}

string
CLAudio::toString() const {
  return "{CLAudio}";
}

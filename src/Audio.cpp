#include "Audio.h"

Audio::Audio(const string &name, bool looping):
  Component(TYPE), name_(name), looping_(looping) {
}

Audio::~Audio() {
}

string
Audio::toString() const {
  return "{Audio name=" + name_ + "}";
}

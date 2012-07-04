#include "Audio.h"

Audio::Audio(const string &name):
  Component(TYPE), name_(name) {
}

Audio::~Audio() {
}

string
Audio::toString() const {
  return "{Audio name=" + name_ + "}";
}

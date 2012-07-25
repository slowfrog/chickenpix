#include "Audio.h"
#include "ComponentRegistry.h"

Component::Type
Audio::TYPE = AUDIO_TYPE;

Audio::Audio(const string &name, bool looping):
  Component(TYPE), name_(name), looping_(looping), played_(false) {
}

Audio::~Audio() {
}

string
Audio::toString() const {
  return "{Audio name=" + name_ + "}";
}

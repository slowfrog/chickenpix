#include "log.h"
#include "Sounds.h"
#include "Audio.h"

Sounds::Sounds(const string &name, EntityManager &em):
  System(name, em) {
}

Sounds::~Sounds() {
}

void
Sounds::init() {
}

void
Sounds::update(int now) {
  TEntityList entities = _em.getEntities(Audio::TYPE);
  for (TEntityIterator it = entities.begin(); it < entities.end(); ++it) {
    Audio *audio = (*it)->getComponent<Audio>();
    if (!audio->isPlaying()) {
      audio->play();
    }
  }
}

void
Sounds::exit() {
}

string
Sounds::toString() const {
  return "{Sounds-System}";
}

#include "log.h"
#include "Sounds.h"
#include "Audio.h"
#include "Resources.h"

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
  Resources *resources = NULL;
  TEntityList entities = _em.getEntities(Audio::TYPE);
  for (TEntityIterator it = entities.begin(); it < entities.end(); ++it) {
    Entity *entity = *it;
    Audio *audio = entity->getComponent<Audio>();
    // Replace abstract Audio by concrete ones
    if (!audio->isConcrete()) {
      if (!resources) {
        resources = _em.getComponent<Resources>();
      }
      Audio *newAudio = resources->makeAudio(audio->getName(),
                                             audio->isLooping());
      entity->removeComponent(Audio::TYPE);
      entity->addComponent(newAudio);
      audio = newAudio;
    }

    audio->play();
  }
}

void
Sounds::exit() {
}

string
Sounds::toString() const {
  return "{Sounds-System}";
}

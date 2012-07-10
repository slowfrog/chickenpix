#include "log.h"
#include "Sounds.h"
#include "Audio.h"
#include "Resources.h"

Sounds::Sounds(const string &name):
  System(name) {
}

Sounds::~Sounds() {
}

void
Sounds::init( EntityManager&) {
}

void
Sounds::update(EntityManager &em, int now) {
  Resources *resources = NULL;
  TEntityList entities = em.getEntities(Audio::TYPE);
  for (TEntityIterator it = entities.begin(); it < entities.end(); ++it) {
    Entity *entity = *it;
    Audio *audio = entity->getComponent<Audio>();
    // Replace abstract Audio by concrete ones
    if (!audio->isConcrete()) {
      if (!resources) {
        resources = em.getComponent<Resources>();
      }
      Audio *newAudio = resources->makeAudio(audio->getName(),
                                             audio->isLooping());
      entity->removeComponent(Audio::TYPE);
      entity->addComponent(newAudio);
      audio = newAudio;
    }

    if (!audio->isPlaying()) {
      if (!audio->hasPlayed()) {
        audio->play();
      } else {
        entity->removeComponent(Audio::TYPE);
      }
    }
  }
}

void
Sounds::exit( EntityManager&) {
}

string
Sounds::toString() const {
  return "{Sounds-System}";
}

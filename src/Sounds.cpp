/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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

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
 
#include <sstream>

#include "Animation.h"
#include "Animated.h"
#include "Resources.h"
#include "Mobile.h"

Animation::Animation( string const &name):
  System( name) {
}

Animation::~Animation() {
}

void
Animation::init( EntityManager&) {
}

void
Animation::update(EntityManager &em, int now) {
  Resources *resources = em.getComponent<Resources>();

  Entity *entity = em.getById(em.getFirstByTag("HERO"));
  Mobile *m = entity->getComponent<Mobile>();
  Animated *a = entity->getComponent<Animated>();
  if (m->getSpeedX() < 0) {
    a->setAnimation("man_walk_left");
  } else if (m->getSpeedX() > 0) {
    a->setAnimation("man_walk_right");
  } else if (m->getSpeedY() < 0) {
    a->setAnimation("man_walk_up");
  } else if (m->getSpeedY() > 0) {
    a->setAnimation("man_walk_down");
  } else {
    string const &curAnim = a->getAnimation();
    if (curAnim.substr(0, 8) == "man_walk") {
      a->setAnimation(string("man_stand") + curAnim.substr(8));
    }
  }
  
  vector<Entity *> anims = em.getEntities(Animated::TYPE);
  for (vector<Entity *>::iterator it = anims.begin(); it < anims.end(); it++) {
    Entity *entity = *it;
    Animated *anim = entity->getComponent<Animated>();
    if (anim->hasChanged()) {
      entity->removeComponent(BVisual::TYPE);
      entity->addComponent(resources->makeSprite(anim->getAnimation()));
      anim->setChanged(false);
    }
  }
}

void
Animation::exit( EntityManager&) {
}

string
Animation::toString() const {
  ostringstream out;
  out << "{Animation-System}" << ends;
  return out.str();
}

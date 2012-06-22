#include <sstream>

#include "Animation.h"
#include "Animated.h"
#include "Resources.h"

Animation::Animation(string const &name, EntityManager &em):
  System(name, em) {
}

Animation::~Animation() {
}

void
Animation::init() {
}

void
Animation::update(int now) {
  Resources *resources = em.getComponent<Resources>();
  
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
Animation::exit() {
}

string
Animation::toString() const {
  ostringstream out;
  out << "{Animation-System}" << ends;
  return out.str();
}

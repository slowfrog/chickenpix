#include <sstream>

#include "Animation.h"
#include "Animated.h"
#include "Resources.h"
#include "Mobile.h"

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
  Resources *resources = _em.getComponent<Resources>();

  Entity *entity = _em.getById(_em.getFirstByTag("HERO"));
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
  
  vector<Entity *> anims = _em.getEntities(Animated::TYPE);
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

#include "WrappedEntity.h"

const Entity::Type WrappedEntity::TYPE = 2;

WrappedEntity::WrappedEntity(Entity &src):
  Entity(src, TYPE), wrapper(wrapEntity(this)) {
  src.releaseComponents();
}

WrappedEntity::~WrappedEntity() {
  Py_DECREF(wrapper);
}

PyObject *
WrappedEntity::getWrapper() const {
  return wrapper;
}

WrappedEntity *
WrappedEntity::wrap(EntityManager &em, Entity *entity) {
  if (isInstance(entity)) {
    return (WrappedEntity *) entity;
  } else {
    WrappedEntity *ret = new WrappedEntity(*entity);
    em.replaceEntity(entity->getId(), ret);
    return ret;
  }
}

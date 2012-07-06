#pragma once

#include "Types.h"
#include "Component.h"

class Collider: public Component {
private:
  /** If a collider is solid, other colliders cannot overlap. */
  bool solid_;
  /** Size of the box used for collision computation. */
  float size_;
  /** List of entities that collide. */
  TEntityIdList collisions_;

public:
  static const Type TYPE = COLLIDER_TYPE;
  Collider(bool solid, float size);
  virtual ~Collider();

  inline
  bool isSolid() const {
    return solid_;
  }
  inline
  void setSolid(bool solid) {
    solid_ = solid;
  }
  inline
  float getSize() const {
    return size_;
  }
  inline
  void setSize(float size) {
    size_ = size;
  }

  void clearCollisions();
  void addCollision(Entity *entity);
  const TEntityIdList &getCollisions() const;
    
  
  virtual string toString() const;
};

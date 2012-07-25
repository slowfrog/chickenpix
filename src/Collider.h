#pragma once

#include "Types.h"
#include "Component.h"

class Collider: public Component {
private:
  /** If a collider is solid, other colliders cannot overlap. */
  bool solid_;
  /** Distance between the transform and the left side of the collision box */
  float left_;
  /** Distance between the transform and the top side of the collision box */
  float top_;
  /** Distance between the transform and the right side of the collision box */
  float right_;
  /** Distance between the transform and the bottom side of the collision box */
  float bottom_;
  /** List of entities that collide. */
  TEntityIdList collisions_;

public:
  static Type TYPE;
  Collider(bool solid, float size);
  Collider(bool solid, float left, float top, float right, float bottom);
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
  float getLeft() const {
    return left_;
  }
  inline
  void setLeft(float left) {
    left_ = left;
  }
  inline
  float getTop() const {
    return top_;
  }
  inline
  void setTop(float top) {
    top_ = top;
  }
  inline
  float getRight() const {
    return right_;
  }
  inline
  void setRight(float right) {
    right_ = right;
  }
  inline
  float getBottom() const {
    return bottom_;
  }
  inline
  void setBottom(float bottom) {
    bottom_ = bottom;
  }
  inline
  void setSize(float size) {
    left_ = size;
    top_ = size;
    right_ = size;
    bottom_ = size;
  }

  void clearCollisions();
  void addCollision(Entity *entity);
  const TEntityIdList &getCollisions() const;
    
  
  virtual string toString() const;
};

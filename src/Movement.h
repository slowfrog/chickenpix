#pragma once

#include "System.h"
class Collider;

class Movement: public System {
public:
  Movement(string const &name, EntityManager &em);
  virtual ~Movement();

  virtual void init();
  virtual void update(int now);
  virtual void exit();
  
  inline SystemType getType() const { return MOVEMENT_TYPE;}

  virtual string toString() const;

private:
  void clearCollisions() const;
  bool resolveCollisions(Entity *ecol, Collider *col) const;
  TEntityList findCollisions(Entity *ecol, Collider *col) const;
  static bool collide(Entity *ecol1, Collider *col1,
                      Entity *ecol2, Collider *col2);
};

#pragma once

#include "System.h"
class Collider;

class Movement: public System {
public:
  Movement( string const &name);
  virtual ~Movement();

  virtual void init   ( EntityManager &);
  virtual void update ( EntityManager &, int now);
  virtual void exit   ( EntityManager &);
  
  inline SystemType getType() const { return MOVEMENT_TYPE;}

  virtual string toString() const;

private:
  TEntityList findCollisions(EntityManager&, Entity *ecol, Collider *col) const;
  static bool collide(Entity *ecol1, Collider *col1,
                      Entity *ecol2, Collider *col2);
};

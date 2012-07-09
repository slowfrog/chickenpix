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
  bool resolveCollisions(Entity *ecol, Collider *col, float dx, float dy,
                         float &dxAllowed, float &dyAllowed) const;
  static bool overlap(float minx1, float maxx1, float miny1, float maxy1,
                      float minx2, float maxx2, float miny2, float maxy2);
  static bool collide(Entity *ecol1, Collider *col1,
                      Entity *ecol2, Collider *col2,
                      float dx, float dy, float &dxAllowed, float &dyAllowed);
};

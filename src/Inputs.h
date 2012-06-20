#pragma once

#include "System.h"

class Inputs: public System {
protected:
  bool exitRequested;
public:
  enum Key {
    Num0 = 0,
    Num1 = 1,
    Num2 = 2,
    Num3 = 3,
    Num4 = 4,
    Num5 = 5,
    Num6 = 6,
    Num7 = 7,
    Num8 = 8,
    Num9 = 9,
    Space = 10,
    Up = 11,
    Down = 12,
    Left = 13,
    Right = 14,
    Escape = 15
  };
  
  Inputs(string const &name, EntityManager &em);
  virtual ~Inputs();

  virtual bool isKeyDown(Key key) const = 0;
  
  virtual void init() = 0;
  virtual void pumpEvents() = 0;
  virtual void update(int now);
  virtual void exit() = 0;

  bool isExitRequested() const;
  
  virtual string toString() const;

private:
  void moveHero(int now);
};

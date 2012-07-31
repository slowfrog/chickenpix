#pragma once

#include "ButtonController.h"

// Forwards
class EntityManager;
class Entity;
class InputState;

// Manage control for fight system
class FightController {
private:
  FightController() {};
  ~FightController() {};
  
protected:
  //void checkPos( const InputState::MousePos&);
public:
  
  static
  void update(EntityManager &em, Entity &entity, const InputState &input,
              int now);
};
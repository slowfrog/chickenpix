#pragma once

// Forwards
class EntityManager;
class Entity;
class InputState;

// Manage control for fight system
class FightController {
private:
  FightController() {};
  ~FightController() {};
public:
  
  static
  void update(EntityManager &em, Entity &entity, const InputState &input,
              int now);
};
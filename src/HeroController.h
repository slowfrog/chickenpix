#pragma once

class EntityManager;
class Entity;
class InputState;

class HeroController {
private:
  HeroController() {};
  ~HeroController() {};
public:
  
  static
  void update(EntityManager &em, Entity &entity, const InputState &input,
              int now);
};

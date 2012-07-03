#pragma once

class EntityManager;
class Entity;
class InputState;

class ButtonController {
private:
  ButtonController() {};
  ~ButtonController() {};
public:
  static
  void update(EntityManager &em, Entity &entity, const InputState &input,
              int now);
};

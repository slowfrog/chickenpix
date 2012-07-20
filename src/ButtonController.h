#pragma once

#include <string>
using namespace std;

class EntityManager;
class Entity;
class InputState;

class ButtonController {
private:
  ButtonController() {};
  ~ButtonController() {};
public:
  static string ButtonDown;
  
  static
  void update(EntityManager &em, Entity &entity, const InputState &input,
              int now);
};

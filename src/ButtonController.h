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
  // The button has just been down this frame
  static const string &ButtonJustDown;
  // The button is down but was already down previously
  static const string &ButtonDown;
  // The button was down and has just been released: it's a click
  static const string &ButtonClicked;
  
  static
  void update(EntityManager &em, Entity &entity, const InputState &input,
              int now);
};

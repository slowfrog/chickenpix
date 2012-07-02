#pragma once

/** This is an interface allowing to ask for the current state of all input devices. It is
 *  implemented specifically by each back-end. An instance is injected into the Input
 *  component so that it can do what it wants with it. */
class InputState {
public:
  struct MousePos {
    int x;
    int y;

    MousePos(int x, int y):
      x(x), y(y) {
	}
  };

  enum MouseButton {
    LeftButton = 0,
    RightButton = 1,
    MiddleButton = 2
  };
    
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

  inline
  InputState() {};
  inline
  virtual ~InputState() {};

  virtual bool isKeyDown(Key k) const = 0;
  virtual bool isButtonDown(MouseButton b) const = 0;
  virtual MousePos getMousePosition() const = 0;
  // Might be useful later
  // virtual bool isKeyJustDown(Key const k) const = 0;
  // virtual bool isKeyJustUp(Key const k) const = 0;
};

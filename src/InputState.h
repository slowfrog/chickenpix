#pragma once

#include <string>
using namespace std;

class VisualContext;

/** This is an interface allowing to ask for the current state of all input
 *  devices. It is implemented specifically by each back-end. It also has a
 *  reference to the VisualContext, because the visual state might participate
 *  in some input computations.
 */
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
    Escape = 15,
    Tab =16,
    A = 17,
    B = 18,
    C = 19,
    D = 20,
    E = 21,
    F = 22,
    G = 23,
    H = 24,
    I = 25,
    J = 26,
    K = 27,
    L = 28,
    M = 29,
    N = 30,
    O = 31,
    P = 32,
    Q = 33,
    R = 34,
    S = 35,
    T = 36,
    U = 37,
    V = 38,
    W = 39,
    X = 40,
    Y = 41,
    Z = 42
  };

  static string KEY_NAMES[];

  inline
  InputState() {};
  inline
  virtual ~InputState() {};

  virtual VisualContext &getVisualContext() const = 0;
  virtual bool isKeyDown(Key k) const = 0;
  virtual bool isButtonDown(MouseButton b) const = 0;
  virtual MousePos getMousePosition() const = 0;
  // Might be useful later
  // virtual bool isKeyJustDown(Key const k) const = 0;
  // virtual bool isKeyJustUp(Key const k) const = 0;
};

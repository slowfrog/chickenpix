#pragma once

#include <string>

#include "Component.h"

class Scriptable: public Component {
private:
  string _name;
  bool _initDone;
  bool _exitDone;
public:
  static const Type TYPE = SCRIPTABLE_TYPE;
  Scriptable(string const &name);
  virtual ~Scriptable();

  inline string const &getName() const {
    return _name;
  }
  virtual void update(int now);

  inline bool isInitDone() const {
    return _initDone;
  }
  inline void setInitDone(bool done) {
    _initDone = done;
  }
  inline bool isExitDone() const {
    return _exitDone;
  }
  inline void setExitDone(bool done) {
    _exitDone = done;
  }

  virtual string toString() const;
};

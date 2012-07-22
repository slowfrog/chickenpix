#pragma once

#include <string>
#include "Component.h"

class Scriptable: public Component {
private:
  string name_;
  bool initDone_;
  bool exitDone_;
public:
  static Type TYPE;
  Scriptable(string const &name);
  virtual ~Scriptable();

  inline string const &getName() const {
    return name_;
  }
  virtual void update(int now);

  inline bool isInitDone() const {
    return initDone_;
  }
  inline void setInitDone(bool done) {
    initDone_ = done;
  }
  inline bool isExitDone() const {
    return exitDone_;
  }
  inline void setExitDone(bool done) {
    exitDone_ = done;
  }

  virtual string toString() const;
};

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "System.h"

class CLRender: public System {
public:
  CL_DisplayWindow *window;
  
public:
  CLRender(string const &name, EntityManager &em);
  virtual ~CLRender();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  virtual string toString() const;
};

#pragma once
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "System.h"
#include "CLResources.h"

class CLLoader: public System {
private:
public:
  CLLoader(string const &name, EntityManager &em);
  virtual ~CLLoader();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  virtual string toString() const;

private:
  void addSprite(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                 Resources *resources, string const &name);
};

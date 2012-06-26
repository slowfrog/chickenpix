#pragma once

#include "Resources.h"
#include "System.h"
#include "VisualContext.h"

class Loader: public System {
public:
  Loader(string const &name, EntityManager &em);
  virtual ~Loader();
  virtual void init();
  virtual void update(int now);
  virtual void exit();
  virtual void addImage(string const &path, Resources *resources, string const &alias="") = 0;
  virtual void addFont(string const &path, int size, Resources *resources, string const &alias="") = 0;
  virtual void addSprite(string const &resourceFile, string const &path, Resources *resources,
                         string const &name) = 0;
  virtual void loadLevel(string const &name);
  virtual string toString() const;
};

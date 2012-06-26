#pragma once
#include "CL.h"
#include "../Loader.h"
#include "../Resources.h"

class CLLoader: public Loader {
public:
  CLLoader(string const &name, EntityManager &em);
  virtual ~CLLoader();

  virtual void addImage(string const &path, Resources *resources, string const &alias="");
  virtual void addFont(string const &path, int size, Resources *resources, string const &alias="");
  virtual void addSprite(string const &resourceFile, string const &path, Resources *resources,
                         string const &name);
  virtual string toString() const;

private:
  void addImage(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                Resources *resources, string const &name);
  void addSprite(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                 Resources *resources, string const &name);
  void addFont(string const &path, CL_ResourceManager *clresources, Resources *resources,
               string const &name);
};

#pragma once
#include "CL.h"
#include "../Loader.h"
#include "../Resources.h"

class CLLoader: public Loader {
private:
public:
  CLLoader(string const &name, EntityManager &em);
  virtual ~CLLoader();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  virtual void addImage(VisualContext &vc, string const &path, Resources *resources,
                        string const &alias="");
  virtual void addFont(VisualContext &vc, string const &path, int size, Resources *resources,
                       string const &alias="");
  virtual string toString() const;

private:
  void addImage(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                Resources *resources, string const &name);
  void addSprite(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                 Resources *resources, string const &name);
  void addFont(string const &path, CL_ResourceManager *clresources, Resources *resources,
               string const &name);
};

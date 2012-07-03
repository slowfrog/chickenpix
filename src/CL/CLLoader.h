#pragma once
#include "CL.h"
#include "../Loader.h"
#include "../Resources.h"

class CLLoader: public Loader {
private:
  CL_ResourceManager *clresources;
public:
  CLLoader(string const &name, EntityManager &em, string const &resourceFile);
  virtual ~CLLoader();

  virtual void initResources();
  virtual void addImage(string const &path, Resources *resources,
                        string const &alias="") const;
  virtual void addFont(string const &path, int size, Resources *resources,
                       string const &alias="");
  virtual void addSprite(string const &path, Resources *resources,
                         string const &name);
  virtual void addAudio(string const &path, Resources *resources,
                        string const &alias);
  virtual string toString() const;

private:
  void addImage(CL_GraphicContext &gc, string const &path,
                CL_ResourceManager *clresources,
                Resources *resources, string const &name);
  void addSprite(CL_GraphicContext &gc, string const &path,
                 CL_ResourceManager *clresources,
                 Resources *resources, string const &name);
  void addFont(string const &path, CL_ResourceManager *clresources,
               Resources *resources, string const &name);
  void addAudio(string const &path, CL_ResourceManager *clresources,
                Resources *resources, string const &name);
};

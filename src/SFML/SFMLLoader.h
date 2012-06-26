#pragma once
#include "../Resources.h"
#include "../Loader.h"

class TiXmlDocument;

class SFMLLoader: public Loader {
  TiXmlDocument *doc;
public:
  SFMLLoader(string const &name, EntityManager &em, string const &resourceFile);
  virtual ~SFMLLoader();

  virtual void initResources();
  virtual void addImage(string const &path, Resources *resources, string const &alias="");
  virtual void addFont(string const &path, int size, Resources *resources, string const &alias="");
  virtual void addSprite(string const &path, Resources *resources, string const &name);
  virtual string toString() const;

private:
  void loadSpriteFromXML(string const &filename, TiXmlDocument *doc, string const &path,
                         Resources *resources, string const &name);

};

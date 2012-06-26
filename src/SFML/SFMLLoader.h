#pragma once
#include "../Resources.h"
#include "../Loader.h"

class TiXmlDocument;

class SFMLLoader: public Loader {
public:
  SFMLLoader(string const &name, EntityManager &em);
  virtual ~SFMLLoader();

  virtual void init();
  virtual void update(int now);
  virtual void exit();
  virtual void addImage(VisualContext &vc, string const &path, Resources *resources,
                        string const &alias="");
  virtual void addFont(VisualContext &vc, string const &path, int size, Resources *resources,
                       string const &alias="");

  virtual string toString() const;

private:
  void loadSpriteFromXML(string const &filename, TiXmlDocument *doc, string const &path,
                         Resources *resources, string const &name);

};

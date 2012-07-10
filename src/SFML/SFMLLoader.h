#pragma once
#include "../Resources.h"
#include "../Loader.h"

class TiXmlDocument;
class TiXmlElement;

class SFMLLoader: public Loader {
  friend class SFMLSystemFactory; // To init Xml doc
  TiXmlDocument *doc;
public:
  SFMLLoader( string const &name);
  virtual ~SFMLLoader();
  
  // Overload
  virtual void addImage  ( Resources *resources);
  virtual void addSprites( Resources *resources);
  virtual void addFont   ( Resources *resources);
  virtual void addAudio  ( Resources *resources);
  
  
  virtual void addImage  ( string const &path, Resources *resources,
                           string const &alias="") const;
  virtual void addFont   ( string const &path, int size, Resources *resources,
                           string const &alias="");
  virtual void addSprite ( string const &path, Resources *resources,
                           string const &name);
  virtual void addAudio  ( string const &path, Resources *resources,
                           string const &name);
  
  virtual string toString() const;
  
protected:
  void prepareXml();

private:
  void loadSpriteFromXML(string const &filename, TiXmlDocument *doc,
                         string const &path,
                         Resources *resources, string const &name);
  
  const TiXmlElement * findChild(const TiXmlElement*, string const &);

};

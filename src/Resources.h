#pragma once
#include <map>

#include "Component.h"
#include "VisualContext.h"
#include "BVisual.h"

// Abstract base classes to represent known types of resources
class ResBase {
public:
  virtual ~ResBase() {}
};
class ResImage: public ResBase {
public:
  virtual ~ResImage() {}
};
class ResSprite: public ResBase {
public:
  virtual ~ResSprite() {}
};
class ResFont: public ResBase {
public:
  virtual ~ResFont() {}
};

// Resource 'repository'
class Resources : public Component {
public:
  enum Kind {
    Image = 0,
    Sprite = 1,
    Font = 2
  };
  static const unsigned int KINDS = 3;
  
private:
  map<string, ResBase *> store[KINDS];

protected:
  void setObject(Kind kind, string const &name, ResBase *object);
  ResBase *getObject(Kind kind, string const &name);
  
public:
  static const Type TYPE = RESOURCES_TYPE;

  Resources();
  virtual ~Resources();

  void setImage(string const &name, ResImage *image);
  ResImage *getImage(string const &name);
  void setSprite(string const &name, ResSprite *sprite);
  ResSprite *getSprite(string const &name);
  void setFont(string const &name, ResFont *font);
  ResFont *getFont(string const &name);

  // Factory methods to be implemented in specific implementations
  virtual BVisual *makeImage(VisualContext &vc, string const &name) = 0;
  virtual BVisual *makeSprite(VisualContext &vc, string const &name) = 0;
  virtual BVisual *makeText(VisualContext &vc, string const &text, string const &font) = 0;
  
  virtual string toString() const;
};

inline void Resources::setImage(string const &name, ResImage *image) {
  setObject(Resources::Image, name, image);
}
inline ResImage *Resources::getImage(string const &name) {
  return (ResImage *) getObject(Resources::Image, name);
}
inline void Resources::setSprite(string const &name, ResSprite *sprite) {
  setObject(Resources::Sprite, name, sprite);
}
inline ResSprite *Resources::getSprite(string const &name) {
  return (ResSprite *) getObject(Resources::Sprite, name);
}
inline void Resources::setFont(string const &name, ResFont *font) {
  setObject(Resources::Font, name, font);
}
inline ResFont *Resources::getFont(string const &name) {
  return (ResFont *) getObject(Resources::Font, name);
}
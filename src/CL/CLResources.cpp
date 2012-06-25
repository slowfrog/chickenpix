#include <cassert>
#include <sstream>
#include "CLResources.h"
#include "CLVisualImage.h"
#include "CLVisualSprite.h"
#include "CLVisualText.h"

CLResources::CLResources(CL_DisplayWindow &window):
  Resources(), vc(window) {
}

CLResources::~CLResources() {
}

VisualContext &
CLResources::getVisualContext() {
  return vc;
}

BVisual *
CLResources::makeImage(string const &name) {
  CLResImage *resImage = (CLResImage *) getImage(name);
  if (resImage == NULL) {
    cerr << "Cannot find image: " << name << endl;
    assert(!(resImage == NULL));
  }
  return new CLVisualImage(resImage->get());
}


BVisual *
CLResources::makeSprite(string const &name) {
  CLResSprite *resSprite = (CLResSprite *) getSprite(name);
  if (resSprite == NULL) {
    cerr << "Cannot find sprite: " << name << endl;
    assert(!(resSprite == NULL));
  }
  CL_Sprite *ret = new CL_Sprite();
  ret->clone(resSprite->get());
  return new CLVisualSprite(ret);
}

BVisual *
CLResources::makeText(string const &text, string const &font, CPColor const &color) {
  CLResFont *resFont = (CLResFont *) getFont(font);
  if (resFont == NULL) {
    cerr << "Cannot find font: " << font << endl;
    assert(!(resFont == NULL));
  }
  return new CLVisualText(text, resFont->get(), CL_Colorf(color.r, color.g, color.b, color.a));
}

string
CLResources::toString() const {
  ostringstream out;
  out << "{CLResources " << "???" << "}" << ends;
  return out.str();
}

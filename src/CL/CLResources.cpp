#include <sstream>
#include "CLResources.h"
#include "CLVisualImage.h"
#include "CLVisualSprite.h"
#include "CLVisualText.h"

CLResources::CLResources():
  Resources() {
}

CLResources::~CLResources() {
}


BVisual *
CLResources::makeImage(VisualContext &vc, string const &name) {
  CLResImage *resImage = (CLResImage *) getImage(name);
  return new CLVisualImage(resImage->get());
}


BVisual *
CLResources::makeSprite(VisualContext &vc, string const &name) {
  CLResSprite *resSprite = (CLResSprite *) getSprite(name);
  return new CLVisualSprite(new CL_Sprite(((CLVisualContext &)vc).getGraphicContext(),
                                          resSprite->get()));
}

BVisual *
CLResources::makeText(VisualContext &vc, string const &text, string const &font) {
  CLResFont *resFont = (CLResFont *) getFont(font);
  return new CLVisualText(text, resFont->get(), CL_Colorf::white);
}

string
CLResources::toString() const {
  ostringstream out;
  out << "{CLResources " << "???" << "}" << ends;
  return out.str();
}

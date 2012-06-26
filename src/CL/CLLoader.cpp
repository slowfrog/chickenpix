#include <iostream>
#include <sstream>
#include "CLLoader.h"
#include "CLResources.h"
#include "CLVisualImage.h"
#include "CLVisualSprite.h"
#include "CLVisualText.h"
#include "../Animated.h"
#include "../Input.h"
#include "../Scriptable.h"
#include "../Transform.h"

CLLoader::CLLoader(string const &name, EntityManager &em):
  Loader(name, em) {
}

CLLoader::~CLLoader() {
}

void
CLLoader::addImage(string const &path, Resources *resources, string const &alias) {
  VisualContext &vc = resources->getVisualContext();
  CL_GraphicContext &gc = ((CLVisualContext &) vc).getGraphicContext();
  CL_Image *img = new CL_Image(gc, path);
  resources->setImage(path, new CLResImage(img));
  if (alias.size() > 0) {
    resources->setImage(alias, new CLResImage(img));
  }
}

void
CLLoader::addImage(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                   Resources *resources, string const &name) {
  resources->setImage(name, new CLResImage(new CL_Image(gc, path, clresources)));
}

void
CLLoader::addSprite(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                    Resources *resources, string const &name) {
  resources->setSprite(name, new CLResSprite(new CL_Sprite(gc, path, clresources)));
}

void
CLLoader::addFont(string const &path, int size, Resources *resources, string const &alias) {
  int realSize = (4 * size) / 3;
  CL_FontDescription desc;
  desc.set_typeface_name(path);
  desc.set_height(realSize);
  desc.set_anti_alias(true);
  desc.set_subpixel(false);
  CL_Font_Freetype *font = new CL_Font_Freetype(desc);
  resources->setFont(path, new CLResFont(font));
  if (alias.length() > 0) {
    resources->setFont(alias, new CLResFont(font));
  }
}

void
CLLoader::addFont(string const &path, CL_ResourceManager *clresources,
                  Resources *resources, string const &name) {
  resources->setFont(name, new CLResFont(new CL_Font_Freetype(path, clresources)));
}

void
CLLoader::addSprite(string const &resourceFile, string const &path, Resources *resources,
                    string const &name) {
  CL_ResourceManager clresources(resourceFile);
  CLVisualContext &vc = (CLVisualContext &) resources->getVisualContext();
  CL_GraphicContext &gc = vc.getGraphicContext();
  addSprite(gc, path, &clresources, resources, name);
}

string
CLLoader::toString() const {
  ostringstream out;
  out << "{CLLoader-System name=" << getName() << "}" << ends;
  return out.str();
}

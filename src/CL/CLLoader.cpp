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
CLLoader::addFont(string const &path, CL_ResourceManager *clresources,
                  Resources *resources, string const &name) {
  resources->setFont(name, new CLResFont(new CL_Font_Freetype(path, clresources)));
}

void
CLLoader::init() {
  Resources *resources = em.getComponent<Resources>();
  CLVisualContext &vc = (CLVisualContext &) resources->getVisualContext();
  CL_GraphicContext &gc = vc.getGraphicContext();

  CL_ResourceManager clresources("resources/resources.xml");
  addImage(gc, "images/house", &clresources, resources, "house");
  addImage(gc, "images/map", &clresources, resources, "map");
  
  addSprite(gc, "sprites/walk_left", &clresources, resources, "man_walk_left");
  addSprite(gc, "sprites/walk_right", &clresources, resources, "man_walk_right");
  addSprite(gc, "sprites/walk_up", &clresources, resources, "man_walk_up");
  addSprite(gc, "sprites/walk_down", &clresources, resources, "man_walk_down");
  addSprite(gc, "sprites/wait", &clresources, resources, "man_still");

  addFont("fonts/sans_big", &clresources, resources, "sans_big");
  addFont("fonts/sans_small", &clresources, resources, "sans_small");

  loadLevel("start");
}

void
CLLoader::update(int now) {
}

void
CLLoader::exit() {
}

string
CLLoader::toString() const {
  ostringstream out;
  out << "{CLLoader-System name=" << getName() << "}" << ends;
  return out.str();
}

/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <cassert>
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

CLLoader::CLLoader(string const &name):
  Loader(name), clresources(NULL) {
}

CLLoader::~CLLoader() {
  if (clresources) {
    delete clresources;
  }
}

void
CLLoader::initResources() {
  clresources = new CL_ResourceManager(resourceFile);
}

void
CLLoader::addImage(string const &path, Resources *resources, string const &alias) const {
  VisualContext &vc = resources->getVisualContext();
  CL_GraphicContext &gc = ((CLVisualContext &) vc).getGraphicContext();
  CL_Image *img;
  try {
    img = new CL_Image(gc, path);
  } catch (CL_Exception e) {
    cerr << "Error building CL_Image: " << e.what() << endl;
    return;
  }
  resources->setImage(path, new CLResImage(img));
  if (alias.size() > 0) {
    resources->setImage(alias, new CLResImage(img));
  }
}

void
CLLoader::addImage(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                   Resources *resources, string const &name) {
  try {
    resources->setImage(name, new CLResImage(new CL_Image(gc, path, clresources)));
  } catch (CL_Exception e) {
    cerr << "Error building CL_Image: " << e.what() << endl;
  }
}

void
CLLoader::addSprite(CL_GraphicContext &gc, string const &path, CL_ResourceManager *clresources,
                    Resources *resources, string const &name) {
  try {
    resources->setSprite(name, new CLResSprite(new CL_Sprite(gc, path, clresources)));
  } catch (CL_Exception e) {
    cerr << "Error building CL_Sprite: " << e.what() << endl;
  }
}

void
CLLoader::addFont(string const &path, int size, Resources *resources, string const &alias) {
  int realSize = (4 * size) / 3;
  CL_FontDescription desc;
  desc.set_typeface_name(path);
  desc.set_height(realSize);
  desc.set_anti_alias(true);
  desc.set_subpixel(false);
  CL_Font_Freetype *font;
  try {
    font = new CL_Font_Freetype(desc);
  } catch (CL_Exception e) {
    cerr << "Error building CL_Font: " << e.what() << endl;
    return;
  }
    
  resources->setFont(path, new CLResFont(font));
  if (alias.length() > 0) {
    resources->setFont(alias, new CLResFont(font));
  }
}

void
CLLoader::addFont(string const &path, CL_ResourceManager *clresources,
                  Resources *resources, string const &name) {
  try {
    resources->setFont(name, new CLResFont(new CL_Font_Freetype(path, clresources)));
  } catch (CL_Exception e) {
    cerr << "Error building CL_Font: " << e.what() << endl;
  }
}

void
CLLoader::addSprite(string const &path, Resources *resources, string const &name) {
  if (clresources == NULL) {
    cerr << "Resource file not loaded: " << resourceFile << endl;
    assert(!(clresources == NULL));
  }
  CLVisualContext &vc = (CLVisualContext &) resources->getVisualContext();
  CL_GraphicContext &gc = vc.getGraphicContext();
  addSprite(gc, path, clresources, resources, name);
}

void
CLLoader::addAudio(string const &path, Resources *resources,
                   string const &alias) {
  CL_SoundBuffer *audio;
  try {
    audio = new CL_SoundBuffer(path);
  } catch (CL_Exception e) {
    cerr << "Error building CL_SoundBuffer: " << e.what() << endl;
    return;
  }
    
  resources->setAudio(path, new CLResAudio(audio));
  if (alias.length() > 0) {
    resources->setAudio(alias, new CLResAudio(audio));
  }
}

void
CLLoader::addAudio(string const &path, CL_ResourceManager *clresources,
                   Resources *resources, string const &name) {
  try {
    resources->setAudio(name,
                        new CLResAudio(new CL_SoundBuffer(path, clresources)));
  } catch (CL_Exception e) {
    cerr << "Error building CL_SoundBuffer: " << e.what() << endl;
  }
}

// void
// CLLoader::addImage  ( Resources *resources) {
// }

// void
// CLLoader::addSprites( Resources *resources) {
// }

// void
// CLLoader::addFont   ( Resources *resources) {
// }

// void
// CLLoader::addAudio  ( Resources *resources) {
// }

string
CLLoader::toString() const {
  ostringstream out;
  out << "{CLLoader-System name=" << getName() << "}" << ends;
  return out.str();
}


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
 
#pragma once
#include "CL.h"
#include "../Loader.h"
#include "../Resources.h"

class CLLoader: public Loader {
private:
  CL_ResourceManager *clresources;
public:
  CLLoader(string const &name);
  virtual ~CLLoader();

  // virtual void addImage  ( Resources *resources);
  // virtual void addSprites( Resources *resources);
  // virtual void addFont   ( Resources *resources);
  // virtual void addAudio  ( Resources *resources);
  
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

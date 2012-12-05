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
#include "../Resources.h"
#include "../Loader.h"

class TiXmlDocument;
class TiXmlElement;

class SFMLLoader: public Loader {
  friend class SFMLSystemFactory; // To init Xml doc
  //TiXmlDocument *doc;
public:
  SFMLLoader( string const &name);
  virtual ~SFMLLoader();
  
  // Overload
  // virtual void addImage  ( Resources *resources);
  // virtual void addSprites( Resources *resources);
  // virtual void addFont   ( Resources *resources);
  // virtual void addAudio  ( Resources *resources);
  
  
  virtual void addImage  ( string const &path, Resources *resources,
                           string const &alias="") const;
  virtual void addFont   ( string const &path, int size, Resources *resources,
                           string const &alias="");
  virtual void addSprite ( string const &path, Resources *resources,
                           string const &name);
  virtual void addAudio  ( string const &path, Resources *resources,
                           string const &name);
  
  virtual string toString() const;
  
// protected:
//   void prepareXml();

private:
  void loadSpriteFromXML(string const &filename, TiXmlDocument *doc,
                         string const &path,
                         Resources *resources, string const &name);
  
  // const TiXmlElement * findChild(const TiXmlElement*, string const &);

};

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

#include <map>
#include <vector>
#include <string>

//#include "Singleton.h"
#include "Entity.h"

// Contants
#define NOT_FOUND     999999999

/**/
class CTagEntityMng
{
public:
  typedef Entity::Id              TEntityId;
  typedef std::vector<TEntityId>  TCollectionIdEntity;
  
  // start here
  typedef Entity::Id              TId;
  typedef std::vector<TId>        TVId;
  
  typedef std::string             TTag;
  typedef std::vector<TTag>       TVTag;
  
  typedef std::map<TTag, TId>     TMTagId;
  typedef std::map<TTag, TVId>    TMTagEntityId;
  typedef std::map<TId, TVTag>    TMEntityIdTag;

public:
  CTagEntityMng(){}
  
  /* API */
  void resetTagCollection();
  void registerTag           ( const TId, const TTag&, bool = false);
  void unregisterTag         ( const TTag&);
  void unregisterTagForEntity( const TId, const TTag&);
  
  TId   getFirstEntityByTag( const TTag&);
  TVTag getTagsByEntity( const TId);    
  TVId  getEntitiesByTag( const TTag&);
  
  void toString();
  
protected:
  bool addTag      ( const TId, const TTag&);
  bool addUniqueTag( const TId, const TTag&);
  bool addForEntity( const TId, const TTag&);
  
  bool dropTag      ( const TTag&);
  bool dropUniqueTag( const TTag&);
  bool dropEntityTag( const TTag&);
    
private:
  // List of entity by tag
  TMTagEntityId   mTagE;
  TMTagId         mTagEU;
  // List of tag by entity
  TMEntityIdTag   mETag;
};
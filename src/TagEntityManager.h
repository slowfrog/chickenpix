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
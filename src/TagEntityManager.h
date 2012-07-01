#pragma once

#include <map>
#include <vector>
#include <string>

#include "Singleton.h"
#include "Entity.h"

// Contants
#define NOT_FOUND     -1

/**/
class CTagEntityMng : public CSingleton<CTagEntityMng>
{
public:
  typedef Entity::Id                          TEntityId;
  typedef std::string                         TTag;
  typedef std::vector<TEntityId>              TCollectionIdEntity;
  
  typedef std::map<TTag, TCollectionIdEntity> TMapTagEntity;
  typedef TMapTagEntity::iterator             TMapTagEntityIt;
  typedef TMapTagEntity::const_iterator       TMapTagEntityCIt;
  
  typedef std::map<TTag, TEntityId>           TMapTagUniqEntity;
  typedef TMapTagUniqEntity::iterator         TMapTagUniqEntityIt;
  typedef TMapTagUniqEntity::const_iterator   TMapTagUniqEntityCIt;
  
  typedef std::vector<TTag>                   TCollectionTag;
  typedef std::map<TEntityId, TCollectionTag> TMapEntityTag;
  typedef TMapEntityTag::iterator             TMapEntityTagIt;
  typedef TMapEntityTag::const_iterator       TMapEntityTagCIt;

public:
  CTagEntityMng(){}
  
  /* API */
  void resetTagCollection();
  void registerTag(const unsigned long, const std::string&, const bool =false); 
  void unregisterTag(const std::string&);
  void unregisterTagForEntity( const unsigned long, const std::string&);
  
  const TEntityId            getEntityByTag(const std::string&) const;
  const TCollectionIdEntity& getEntitiesByTag(const std::string&) const;
  const TEntityId            getFirstEntityByTag(const std::string&) const;
  
  const TCollectionTag&      getTagsByEntity( const unsigned long) const;
    
private:
  // List of entity by tag
  TMapTagEntity       mTagE;
  TMapTagUniqEntity   mTagUniqE;
  // List of tag by entity
  TMapEntityTag       mETag;
};
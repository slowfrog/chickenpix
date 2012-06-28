#pragma once

#include <map>
#include <vector>
#include <string>

#include "Singleton.h"

/**/
class CTagEntityMng : public CSingleton<CTagEntityMng>
{
public:
    typedef unsigned long                       TEntityId;
    typedef std::string                         TTag;
    typedef std::vector<TEntityId>              TCollectionIdEntity;
    
    typedef std::map<TTag, TCollectionIdEntity> TMapTagEntity;
    typedef TMapTagEntity::iterator             TMapTagEntityIt;
    typedef TMapTagEntity::const_iterator       TMapTagEntityCIt;

    typedef std::map<TTag, TEntityId>           TMapTagUniqEntity;
    typedef TMapTagUniqEntity::iterator         TMapTagUniqEntityIt;
    typedef TMapTagUniqEntity::const_iterator   TMapTagUniqEntityCIt;

public:
    CTagEntityMng(){}

    /* API */
    void resetTagCollection();
    void registerTag(const unsigned long, const std::string&, const bool =false); 
    void unregisterTag(const std::string&, const bool = false);

    const TEntityId            getEntityByTag(const std::string&) const;
    const TCollectionIdEntity& getEntitiesByTag(const std::string&) const;
    const TEntityId            getFirstEntitiesByTag(const std::string&) const;
    
private:
    TMapTagEntity       _mTagE;
    TMapTagUniqEntity   _mTagUniqE;
};
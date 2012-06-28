#include "../log.h"
#include "TagEntityManager.h"

void 
CTagEntityMng::resetTagCollection(){
  _mTagE.clear();
  _mTagUniqE.clear();
}

void 
CTagEntityMng::registerTag(const unsigned long entityId, const std::string &tag, const bool unique){
  if( !unique ){
    CTagEntityMng::TMapTagEntityIt it = _mTagE.find( tag);
    if ( it != _mTagE.end()){
      (*it).second.push_back( entityId);
    }
    else{
      CTagEntityMng::TCollectionIdEntity vecId;
      vecId.push_back( entityId);
      _mTagE.insert( std::pair<TTag, CTagEntityMng::TCollectionIdEntity> (tag, vecId));
    }
  }
  else{
    _mTagUniqE.erase( tag); /* to be sure! */
    _mTagUniqE.insert( std::pair<TTag, TEntityId> (tag, entityId));
  }
}

void 
CTagEntityMng::unregisterTag(const std::string& tag, bool unique){
  if( !unique ){
    _mTagE.erase( tag);
  }
  else{
    _mTagUniqE.erase( tag);
  }
}

const CTagEntityMng::TEntityId
CTagEntityMng::getEntityByTag(const std::string& tag) const{
  CTagEntityMng::TMapTagUniqEntityCIt it = _mTagUniqE.find( tag);
  if ( it != _mTagUniqE.end()){
    return (*it).second;
  }
  LOG2ERR<<"Tag ["<< tag<<"] not found\n";
  throw "No tag found";
}

const CTagEntityMng::TCollectionIdEntity&
CTagEntityMng::getEntitiesByTag(const std::string& tag) const {
  CTagEntityMng::TMapTagEntityCIt it = _mTagE.find( tag);
  if ( it != _mTagE.end()){
    return (*it).second;
  }
  LOG2ERR<<"Tag ["<< tag<<"] not found\n";
    throw "No tag found";
}

const CTagEntityMng::TEntityId
CTagEntityMng::getFirstEntitiesByTag(const std::string& tag) const {
  CTagEntityMng::TMapTagEntityCIt it = _mTagE.find( tag);
  if ( it != _mTagE.end()){
    return (*it).second.front();
  }
  LOG2ERR<<"Tag ["<< tag<<"] not found\n";
  throw "No tag found";
}

#include "log.h"
#include "TagEntityManager.h"

// Global
CTagEntityMng::TCollectionTag EmptyTag; // pas top

void 
CTagEntityMng::resetTagCollection(){
  mTagE.clear();
  mTagUniqE.clear();
}

void 
CTagEntityMng::registerTag(const unsigned long entityId, const std::string &tag, const bool unique){
  // Tag already exists
  if ( hasTag( entityId, tag)){
    return;
  }
  
  // Add into map(tag,entity)
  if( !unique ){
    CTagEntityMng::TMapTagEntityIt it = mTagE.find( tag);
    if ( it != mTagE.end()){
      (*it).second.push_back( entityId);
    }
    else{
      CTagEntityMng::TCollectionIdEntity vecId;
      vecId.push_back( entityId);
      mTagE.insert( std::pair<TTag, CTagEntityMng::TCollectionIdEntity> (tag, vecId));
    }
  }
  else{
    mTagUniqE.erase( tag); /* to be sure! */
    mTagUniqE.insert( std::pair<TTag, TEntityId> (tag, entityId));
  }
  
  // Add into map(entity,tag)
  TMapEntityTagIt it = mETag.find( entityId);
  if ( it != mETag.end() ){
    (*it).second.push_back( tag);
  }
  else {
    TCollectionTag vec;
    vec.push_back( tag);
    mETag.insert( std::pair<TEntityId, TCollectionTag> ( entityId, vec) );
  }
}

void 
CTagEntityMng::unregisterTag( const std::string& tag){
  long  deleted = mTagE.erase( tag);
  if ( !deleted) {
    mTagUniqE.erase( tag);
  }
}

void 
CTagEntityMng::unregisterTagForEntity( const unsigned long id, const std::string &tag){
  CTagEntityMng::TMapTagEntityCIt it = mTagE.find( tag);
  if ( it != mTagE.end()){
    TCollectionIdEntity vId = (*it).second;
    TCollectionIdEntity::iterator vit = vId.begin();
    for( ; vit != vId.end(); vit++){
      if ( (*vit) == id){
        vId.erase( vit);
        break;
      }
    }
  }
  else{
      mTagUniqE.erase( tag);
  }
}

const CTagEntityMng::TEntityId
CTagEntityMng::getEntityByTag(const std::string& tag) const{
  CTagEntityMng::TMapTagUniqEntityCIt it = mTagUniqE.find( tag);
  if ( it != mTagUniqE.end()){
    return (*it).second;
  }
  LOG2ERR<<"Tag ["<< tag<<"] not found\n";
  return NOT_FOUND;
}

const CTagEntityMng::TCollectionIdEntity&
CTagEntityMng::getEntitiesByTag(const std::string& tag) const {
  CTagEntityMng::TMapTagEntityCIt it = mTagE.find( tag);
  if ( it != mTagE.end()){
    return (*it).second;
  }
  LOG2ERR<<"Tag ["<< tag<<"] not found\n";
  throw -1;
}

const CTagEntityMng::TEntityId
CTagEntityMng::getFirstEntityByTag(const std::string& tag) const {
  CTagEntityMng::TMapTagEntityCIt it = mTagE.find( tag);
  if ( it != mTagE.end()){
    return (*it).second.front();
  }
  LOG2ERR<<"Tag ["<< tag<<"] not found\n";
  return NOT_FOUND;
}

static CTagEntityMng::TCollectionTag EMPTY_COLLECTION;

const CTagEntityMng::TCollectionTag&      
CTagEntityMng::getTagsByEntity( const unsigned long entityId) const{
  CTagEntityMng::TMapEntityTagCIt it = mETag.find( entityId);
  if ( it != mETag.end() ){
    return (*it).second;
  }
  return EMPTY_COLLECTION;
}

bool  
CTagEntityMng::hasTag( const TEntityId id, const TTag& tag){
  TCollectionTag tagCol = getTagsByEntity( id);
  TCollectionTag::const_iterator it = tagCol.begin();
  for (it; it != tagCol.end(); it++) {
    if ( (*it) == tag ) {
      return true;
    }
  }
  return false;
}


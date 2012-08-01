#include "log.h"
#include "TagEntityManager.h"

void 
CTagEntityMng::resetTagCollection(){
  mTagE.clear();
  mTagEU.clear();
  mETag.clear();
}

bool
CTagEntityMng::addTag( const TId id, const TTag& tag){
  TMTagEntityId::iterator it = mTagE.find( tag);
  if ( it == mTagE.end()){
    TVId v;
    v.push_back( id);
    mTagE.insert( std::pair<TTag, TVId>( tag, v));
    return true;
  }
  else{
    for( std::size_t ind=0; ind <(*it).second.size(); ind++){
      if( (*it).second[ind] == id)
        return false;
    }
    (*it).second.push_back( id);
    return true;
  }
}

bool 
CTagEntityMng::addUniqueTag( const TId id, const TTag &tag){
  TMTagId::iterator it = mTagEU.find( tag);
  if ( it == mTagEU.end()){        
    mTagEU.insert( std::pair<TTag, TId>( tag, id));
    return true;
  }
  return false;
}

bool 
CTagEntityMng::addForEntity( const TId id, const TTag &tag){
  TMEntityIdTag::iterator it = mETag.find( id);
  if( it == mETag.end()){
    TVTag v;
    v.push_back( tag);        
    mETag.insert( std::pair<TId, TVTag>( id, v));        
    return true;
  }
  else{
    for( std::size_t ind=0; (*it).second.size(); ind++ ){
      if( (*it).second[ind] == tag ){
        return false;
      }
      (*it).second.push_back( tag);
      return true;
    }
  }
  return false;
}

bool 
CTagEntityMng::dropTag( const TTag &tag){
  std::size_t t = mTagE.erase( tag);
  return (t >0);
}

bool 
CTagEntityMng::dropUniqueTag( const TTag &tag){
  std::size_t t = mTagEU.erase( tag);
  return (t >0);
}

bool 
CTagEntityMng::dropEntityTag( const TTag &tag){
  TMEntityIdTag::iterator it = mETag.begin();
  while( it != mETag.end()){
    for ( std::size_t ind=0; ind<(*it).second.size(); ind++)
    {
      if ( tag == (*it).second[ind]){
        (*it).second.erase( (*it).second.begin() + ind);
      }           
    }    
    if ( (*it).second.empty())
    {
      mETag.erase( (*it).first);
      it = mETag.begin();
    } 
    else{
      it++;
    }
  }
  return true;
}

void 
CTagEntityMng::registerTag(const unsigned long  id, 
                           const std::string    &tag, 
                           const bool           unique
                           )
{
  // Check before insert
  TMTagId::iterator it = mTagEU.find( tag);
  if ( it != mTagEU.end() ) return;
  
  // Add Tag => List of entity
  if ( unique){
    addUniqueTag( id, tag);
  }
  else {
    addTag( id, tag);
  }
  // Add Entity => list of tag
  addForEntity( id, tag);
}

void 
CTagEntityMng::unregisterTag( const std::string& tag){
  //
  if( !dropTag( tag)){
    dropUniqueTag( tag);
  }
  // 
  dropEntityTag( tag);
}

void 
CTagEntityMng::unregisterTagForEntity( const unsigned long id, const std::string &tag){
  TMEntityIdTag::iterator it = mETag.find( id);
  // chack entity
  if ( it == mETag.end()){
    return;
  }
  // Check tag
  TVTag::iterator itt = (*it).second.begin();
  for(; itt != (*it).second.end(); itt++){
    if( tag == (*itt)){
      (*it).second.erase( itt);
      if ( (*it).second.empty() )
      {
        mETag.erase ( (*it).first);
        break;
      }
      itt = (*it).second.begin(); 
    }
  }    
  // Update tag
  TMTagEntityId::iterator ite = mTagE.find( tag);
  if ( ite != mTagE.end() ){
    TVId::iterator iti = (*ite).second.begin();
    for(; iti != (*ite).second.end(); iti++){
      if( id == (*iti)){
        (*ite).second.erase( iti);
        if ( (*ite).second.empty() )
        {
          mTagE.erase ( (*ite).first);
          break;
        }
        iti = (*ite).second.begin(); 
      }
    }
  }
  // Unique
  /*std::size_t t = */
  mTagEU.erase( tag);
}

CTagEntityMng::TVId  
CTagEntityMng::getEntitiesByTag( const TTag &tag){
  TMTagEntityId::iterator it = mTagE.find( tag);
  if ( it != mTagE.end())
  {
    return (*it).second;
  } 
  else
  {
    TVId v;
    TMTagId::iterator it = mTagEU.find( tag);
    if ( it != mTagEU.end() )
    {
      v.push_back( (*it).second);
      return v;
    }
    return v;
  }
}

CTagEntityMng::TId
CTagEntityMng::getFirstEntityByTag( const TTag &tag){
  TVId v = getEntitiesByTag( tag);
  if ( !v.empty())
    return v.front();
  return NOT_FOUND;
}

CTagEntityMng::TVTag       
CTagEntityMng::getTagsByEntity( const TId id){
  TMEntityIdTag::iterator it = mETag.find( id);
  if ( it != mETag.end() )
    return (*it).second;
  return TVTag();
}

void
CTagEntityMng::toString(){
  // List of entity by tag (non unique)
  TMTagEntityId::iterator it = mTagE.begin();
  while( it != mTagE.end()){
    LOG2<<"Tag ["<<(*it).first<<"] : list of entities ";
    for( std::size_t ind=0; ind<(*it).second.size(); ind++)
      LOG2<<"["<<(*it).second[ind]<<"], ";
    LOG2<<"\n";
    it++;
  }
  
  // Unique tag by entity
  TMTagId::iterator itu = mTagEU.begin();
  while( itu != mTagEU.end()){
    LOG2<<"TagU ["<<(*itu).first<<"] ="<<"{"<<(*itu).second<<"}\n";
    itu++;
  }
  
  // List of tag by entity    
  TMEntityIdTag::iterator itt = mETag.begin();
  while( itt != mETag.end()){
    LOG2<<"Entity ["<<(*itt).first<<"] : list of tag ";
    for( std::size_t ind=0; ind<(*itt).second.size(); ind++)
      LOG2<<"["<<(*itt).second[ind]<<"], ";
    LOG2<<"\n";
    itt++;
  }
  LOG2<<"\n";
}


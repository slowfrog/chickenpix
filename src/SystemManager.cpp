#include <cassert>
#include <algorithm>
#include "log.h"
#include "SystemRegistry.h"
#include "TagEntityManager.h"
#include "SystemManager.h"

// Constants
#define BAD_INDEX -1

// Constructor / Destuctor
CSystemManager::CSystemManager():mEMng( NULL), mCurVecSys( NULL){
}

CSystemManager::~CSystemManager(){
  deleteEM();
  mMapEMSys.clear();
}

void 
CSystemManager::deleteEM(){
  for(unsigned int i=0; i < mvEM.size(); i++){
    EntityManager* em = mvEM.back();
    mvEM.pop_back();
    delete em;
  }
}

EntityManager*
CSystemManager::getEM( const std::string &name){
  unsigned int i( 0);
  while( i < mvEM.size() && name !=mvEM[i]->getName()){
    i++;
  }
  assert( i < mvEM.size());
  return mvEM[i];
}

// Create a new entity manager and store it into manager
void  
CSystemManager::createEntityManager( const std::string &name){
  TMapEMSystem::iterator it = mMapEMSys.find( name);
  if ( it == mMapEMSys.end() ){
    mvEM.push_back( new EntityManager( name));
    TSystemCollection vSystem;
    vSystem.resize( MAX_SYSTEM); // size for all systems
    LOG2 << "["<< name<<"][Systems].size()=" << vSystem.size()<< "\n";
    mMapEMSys.insert( std::pair<TId, TSystemCollection>( name, vSystem));
  }
  else {
    LOG2 << "Entity Manager [" << name<<"] already exists...\n";
  }
}

void 
CSystemManager::registerSystem( const std::string &name, System *sys){
  // Check system
  if ( !sys){
    LOG2ERR << "Try to register [NULL] System to entity Manager [" << name<<"]\n";
    return;
  }
  // Add new system
  TMapEMSystem::iterator it = mMapEMSys.find( name);
  if ( it != mMapEMSys.end()) {
    TSystemCollection vec = (*it).second;
    if ( !(*it).second.at(sys->getType())){
      (*it).second[ sys->getType()] = sys;
    }
    else {
      LOG2ERR << "System ["<<sys->getName()<<"] already in manager ["<<name<<"]\n";
    }
  }
  else{
    throw "Register system [" + sys->getName() + "] to unused manager [" + name +"]";
  }
}

void 
CSystemManager::setCurrent( const std::string &name){
  TMapEMSystem::iterator it = mMapEMSys.find( name);
  if ( it != mMapEMSys.end()){
    mCurVecSys  = &((*it).second);
    mEMng       = getEM( name);
  }
  else{
    throw "Could not access current EntityManager ["+ name + "], not found."; 
  }
}

EntityManager&
CSystemManager::getByRef(){
  return *mEMng;
}
EntityManager&
CSystemManager::getByName( const std::string& name){
  return *getEM( name);
}

CSystemManager::TSystemCollection&
CSystemManager::getCurrentSystem(){
  return *mCurVecSys;
}

System*
CSystemManager::getCurrentSystemByType( const SystemType type){
  if ( type >=0 && type <END_OF_LIST){
    return (*mCurVecSys)[type];
  }
  throw "System type out of bound";
}

const CSystemManager::TId  
CSystemManager::getName() const {
  return mEMng->getName();
}

void 
CSystemManager::SystemInit( EntityManager &em){
  TSystemCollection  *pCollec(NULL);
  TMapEMSystem::iterator it = mMapEMSys.find( em.getName());
  pCollec = &((*it).second);
  
  if ( pCollec){
    for (int i = 0; in_ex_itPath[i] != END_OF_LIST; ++i) {
      System *sys = (*pCollec)[in_ex_itPath[i]];
      if (sys) {
        sys->init( em);
      }
    }
  }
}

void
CSystemManager::SystemInit(){
  if ( mCurVecSys && mEMng){
    for (int i = 0; in_ex_itPath[i] != END_OF_LIST; ++i) {
      System *sys = (*mCurVecSys)[in_ex_itPath[i]];
      if (sys) {
        sys->init( *mEMng);
      }
    }
  }
}

void 
CSystemManager::SystemUpdate( int now){
  if ( mCurVecSys && mEMng){
    for (int i = 0; updatePath[i] != END_OF_LIST; ++i) {
      System *sys = (*mCurVecSys)[updatePath[i]];
      if (sys) {
        sys->update( *mEMng, now);
      }
    }
  }
}

void 
CSystemManager::SystemUpdate( EntityManager &em, int now){
  TSystemCollection  *pCollec(NULL);
  TMapEMSystem::iterator it = mMapEMSys.find( em.getName());
  pCollec = &((*it).second);
  
  if ( pCollec){
    for (int i = 0; updatePath[i] != END_OF_LIST; ++i) {
      System *sys = (*pCollec)[updatePath[i]];
      if (sys) {
        sys->update( em, now);
      }
    }
  }
}

void 
CSystemManager::SystemExit(){
  if ( mCurVecSys){
    for (int i = END_OF_LIST - 1; i >= 0; --i) {
      System *sys = (*mCurVecSys)[in_ex_itPath[i]];
      if (sys) {
        sys->exit( *mEMng);
      }
    }
  }
}

void 
CSystemManager::SystemExit( EntityManager &em){
  TSystemCollection  *pCollec(NULL);
  TMapEMSystem::iterator it = mMapEMSys.find( em.getName());
  pCollec = &((*it).second);
  
  if ( pCollec){
    for (int i = END_OF_LIST - 1; i >= 0; --i) {
      System *sys = (*pCollec)[in_ex_itPath[i]];
      if (sys) {
        sys->exit( em);
      }
    }
  }
}

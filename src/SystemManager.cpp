#include <cassert>
#include <algorithm>
#include "log.h"
#include "SystemManager.h"

// Constants
#define BAD_INDEX -1

// Constructor / Destuctor
CSystemManager::CSystemManager():mCurEMName(""), mCurEM(0){
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
    vSystem.resize( MAX_SYSTEM);
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
    LOG2 << "Try to register [NULL] System to entity Manager [" << name<<"]\n";
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
      LOG2 << "System ["<<sys->getName()<<"] already in manager ["<<name<<"]\n";
    }
  }
  else{
    throw "Register system [" + sys->getName() + "] to unused manager " + name;
  }
}

void 
CSystemManager::setCurrent( const std::string &name){
  TMapEMSystem::iterator it = mMapEMSys.find( name);
  if ( it != mMapEMSys.end()){
    mCurEMName  = name;
    mCurVecSys  = &((*it).second);
    mCurEM      = getEM( name);
  }
  else{
    throw "Could not access current EntityManager ["+ name + "], not found."; 
  }
}

EntityManager* 
CSystemManager::getCurrentEntityManager(){
  return mCurEM;
}

CSystemManager::TSystemCollection&
CSystemManager::getCurrentSystem(){
  return *mCurVecSys;
}

System*
CSystemManager::getSystemByType( const SystemType type){
  if ( type >=0 && type <END_OF_LIST){
    return (*mCurVecSys)[type];
  }
  throw "System type out of bound";
}

void 
CSystemManager::SystemInit(){
  if ( mCurVecSys){
    for (int i = 0; in_ex_itPath[i] != END_OF_LIST; ++i) {
      System *sys = (*mCurVecSys)[in_ex_itPath[i]];
      if (sys) {
        sys->init();
      }
    }
  }
}

void 
CSystemManager::SystemUpdate(int now){
  if ( mCurVecSys){
    for (int i = 0; updatePath[i] != END_OF_LIST; ++i) {
      System *sys = (*mCurVecSys)[updatePath[i]];
      if (sys) {
        sys->update(now);
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
        sys->exit();
      }
    }
  }
}

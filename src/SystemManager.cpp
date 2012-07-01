#include <algorithm>
#include "log.h"
#include "SystemManager.h"

// Constants
#define BAD_INDEX -1

// Constructor / Destuctor
CSystemManager::CSystemManager(){
}

CSystemManager::~CSystemManager(){
  deleteEM();
  mMapEMSys.clear();
}

void 
CSystemManager::deleteEM(){
  for(int i=0; i < mvEM.size(); i++){
    EntityManager* em = mvEM.back();
    mvEM.pop_back();
    delete em;
  }
  
}

// Create a new entity manager and store it into manager
void  
CSystemManager::createEntityManager( const std::string &name){
  TMapEMSystem::iterator it = mMapEMSys.find( name);
  if ( it == mMapEMSys.end() ){
    mvEM.push_back( new EntityManager( name));
    mMapEMSys.insert( std::pair<TId, TSystemCollection>( name, TSystemCollection()));
  }
}

void 
CSystemManager::registerSystem( const std::string &name, System *sys){
  // Check system
  if ( !sys){
    return;
  }
  // Add new system
  TMapEMSystem::iterator it = mMapEMSys.find( name);
  if ( it != mMapEMSys.end()) {
    TSystemCollection vec = (*it).second;
    for(int i=0; i< vec.size(); i++){
      if ( vec[i]->getName() == sys->getName()){
        LOG2 << "System ["<<sys->getName()<<"] already in manager ["<<name<<"]\n";
        return; // Already exists in this entity manager
      }
    }
    (*it).second.push_back( sys);
  }
  else{
    throw "Register system [" + sys->getName() + "] to unused manager " + name;
  }
}

void 
CSystemManager::setCurrentEntityManager( const std::string &name){
  TMapEMSystem::iterator it = mMapEMSys.find( name);
  if ( it != mMapEMSys.end()){
    mCurrent    = name;
    mCurrentSys = (*it).second;
  }
  else{
    throw "Could not access current EntityManager ["+ name + "], not found."; 
  }
}

EntityManager* 
CSystemManager::getCurrentEntityManager(){
  if ( !mCurrent.empty()){
    for(int i=0; i< mvEM.size(); i++){
      if ( mCurrent == mvEM[i]->getName()) {
        return mvEM[i];
      }
    }
  }
  return 0;
}

void 
CSystemManager::SystemInit(){
  if ( !mCurrentSys.empty()){
    for(int i=0; i<mCurrentSys.size(); i++){
      mCurrentSys[i]->init();
    }
  }
}

void 
CSystemManager::SystemUpdate(int now){
  if ( !mCurrentSys.empty()){
    for(int i=0; i<mCurrentSys.size(); i++){
      mCurrentSys[i]->update( now);
    }
  }
}

void 
CSystemManager::SystemExit(){
  if ( !mCurrentSys.empty()){
    for(int i=0; i<mCurrentSys.size(); i++){
      mCurrentSys[i]->exit();
    }
  }
}
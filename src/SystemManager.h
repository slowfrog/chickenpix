#pragma once

#include <map>
#include <vector>
#include "Singleton.h"
#include "System.h"
#include "EntityManager.h"

class CSystemManager : public CSingleton<CSystemManager> {
public:
  typedef std::string                       TId;  // Entity Manager name
  
  typedef std::vector<System*>              TSystemCollection;
  typedef std::vector<EntityManager*>       TEntityMngCollection;
  
  typedef std::map<TId, TSystemCollection>  TMapEMSystem;
  
public:
  CSystemManager();
  virtual ~CSystemManager();
  
  void createEntityManager    ( const std::string&);
  void registerSystem         ( const std::string&, System*);
  void setCurrentEntityManager( const std::string&);
  
  EntityManager* getCurrentEntityManager();
  
  void SystemInit   ();
  void SystemUpdate ( int);
  void SystemExit   ();
  
protected:
  void deleteEM();
  
private:
  // Members
  TMapEMSystem          mMapEMSys;
  TEntityMngCollection  mvEM;
  TId                   mCurrent;
  TSystemCollection     mCurrentSys;
};

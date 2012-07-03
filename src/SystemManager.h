#pragma once
#include <map>
#include <vector>
#include "Singleton.h"
#include "System.h"
#include "EntityManager.h"

/*
 System manager
 Goal : manage several systems from one entity Manager
        Allow switch between entity manager
 */
class CSystemManager : public CSingleton<CSystemManager> {
public:
  typedef std::string                       TId;  // Entity Manager name
  
  typedef std::vector<System*>              TSystemCollection;
  typedef std::vector<EntityManager*>       TEntityMngCollection;
  
  typedef std::map<TId, TSystemCollection>  TMapEMSystem;
  
public:
  // Constrcutor/Destrcutor
  CSystemManager();
  virtual ~CSystemManager();
  
  // API
  void createEntityManager    ( const std::string&);
  void registerSystem         ( const std::string&, System*);
  void setCurrent             ( const std::string&);
  
  void SystemInit   ();
  void SystemUpdate ( int);
  void SystemExit   ();
  
  // Accessor
  EntityManager     *getCurrentEntityManager();
  TSystemCollection &getCurrentSystem();
  System            *getSystemByType( const SystemType); 
  
protected:
  // Get entity manager by its name
  EntityManager *getEM( const std::string&);
  // Delete allocated vector of entity manager
  void deleteEM();
  
private:
  // Store elements
  TMapEMSystem          mMapEMSys;
  TEntityMngCollection  mvEM;
  // Manage current elments
  TId                   mCurEMName;
  TSystemCollection     *mCurVecSys;
  EntityManager         *mCurEM;
};

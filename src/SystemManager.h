#pragma once
#include <map>
#include <vector>
#include "System.h"
#include "EntityManager.h"

/*
 System manager
 Goal : manage several systems from one entity Manager
        Allow switch between entity manager
 */
class CSystemManager {
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
  
  void SystemInit   ( EntityManager&);
  void SystemInit   ( );
  void SystemUpdate ( EntityManager&, int);
  void SystemUpdate ( int);
  void SystemExit   ( EntityManager&);
  void SystemExit   ( );
  
  // Accessor(s)
  EntityManager     &getByName( const std::string&);
  EntityManager     &getByRef();
  TSystemCollection &getCurrentSystem();
  System            *getCurrentSystemByType( const SystemType);
  
  const TId         getName() const;
  
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
  TSystemCollection     *mCurVecSys;
  EntityManager         *mEMng;
};

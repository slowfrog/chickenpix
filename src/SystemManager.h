/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
  bool exitRequested          ( ) const;
  
  void SystemInit   ( EntityManager&);
  void SystemInit   ( );
  void SystemUpdate ( EntityManager&, int);
  void SystemUpdate ( int);
  void SystemExit   ( EntityManager&);
  void SystemExit   ( );
  
  // Accessor(s)
  EntityManager     &getByName( const std::string&);
  EntityManager     &getByRef() const;
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

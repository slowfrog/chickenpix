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

#include <cstdlib>
#include <sstream>
#include <map>
#include <time.h>
#include "log.h"
#include "variant.h"
#include "Component.h"

// Stats id Character
#define HEALTH                      0x000100
#define DAMAGE                      0x000200
#define ARMOR_CLASS                 0x000300
#define INITIATIVE                  0x000400

#define TAG_HEALTH                  "Health"
#define TAG_DAMAGE                  "Damage"
#define TAG_ARMOR                   "Armor"
#define TAG_INITATIVE               "Initiative"

#define DEFAULT_NAME_CH             "---"
#define DEFAULT_ID_CH               9999999L
#define DEFAULT_LIFE_THRESHOLD_CH   0L
#define DEFAULT_MIN_STAT            1L

/****************************************************************/
/* Dice                                                         */
/****************************************************************/
template<int N=6>
class CDice
{
public:
    static void init(long n = (long)time( NULL)) { srand( n);}
    static unsigned long rolled() { LOG2DBG<<"N="<<N<<"\n"; return (rand()%N + 1);}
};

/****************************************************************/
/* Stats                                                        */
/****************************************************************/
class Stats {
public:
    typedef std::map<long, CVariant>    TMapVariant;
    typedef TMapVariant::iterator       TMapVariantIt;
    typedef TMapVariant::const_iterator TMapVariantCIt;
    typedef std::pair<long, CVariant>   TLongVariant;
public:
    Stats(){ _mstats.clear();}
    ~Stats(){ _mstats.clear();}
    // API
    void addStat(const long, const CVariant&);
    void removeStat(const long);
    void setStat(const long, const CVariant&);
    CVariant& getStat(const long);
    const CVariant& getStat(const long)const ;
  
  const TMapVariant& get() const { return _mstats;}

    std::string toString() const;
  
protected:
    // Data    
    TMapVariant _mstats;
};


/****************************************************************/
/* CCharacter                                                   */
/****************************************************************/
class Character : public Component
{
public:
  static Type TYPE;
public:
  Character(const string &name=DEFAULT_NAME_CH,
            const unsigned long id= DEFAULT_ID_CH,
            long lt=DEFAULT_LIFE_THRESHOLD_CH);
  Character(const Character&);
  virtual ~Character(){}
  
  inline const unsigned long Id() const {return _id;}
  inline const std::string& Name() const {return _name;}
  
  void addStats(const unsigned id, const CVariant& v){
    _stats.addStat(id, v);
  }
  
  bool isDead() { return _stats.getStat(HEALTH) <= _lifeThreshold; }
  CVariant& get(const unsigned long id) { return _stats.getStat( id);}
  const CVariant& get(const unsigned long id) const { return _stats.getStat( id);}
  
  const Stats& getStats() const { return _stats;}
  
  std::string toString() const;
  
private:
  unsigned long   _id;
  std::string     _name;
  long            _lifeThreshold;
  Stats           _stats;
  // Skill (attaque, defense, fuite)
  // Liste objet (prevoir modificateur)
  // Liste objet equipe
  // pile de modificateurs stack<long, long>
};


// Interface to manipulate Stats in CCharacter
typedef void(*func)(CVariant&, const CVariant&);

void change(Character&, const unsigned long, const CVariant&, func);

void plusVar(CVariant&, const CVariant&);
void minusVar(CVariant&, const CVariant&);




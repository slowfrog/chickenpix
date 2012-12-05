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
 
#include <iostream>
#include "Stats.h"
#include "ComponentRegistry.h"

std::ostream& operator<<( std::ostream &os , const CVariant& v){
    if ( CVariant::eLong == v._kindOfValue )   return os<<v._lValue;
    if ( CVariant::eFloat == v._kindOfValue )  return os<<v._fValue;
    if ( CVariant::eDouble == v._kindOfValue ) return os<<v._dValue;
    if ( CVariant::eString == v._kindOfValue ) return os<<v._sValue;
    return os;
}

/**
*/
void 
Stats::addStat(const long cid, const CVariant& crv){
  TMapVariantIt it = _mstats.find( cid);
  if( it != _mstats.end()){
    (*it).second = crv;
  }
  else{
    _mstats.insert( TLongVariant(cid, crv));
  }
}

/**
*/
void 
Stats::removeStat(const long cid){
  _mstats.erase( cid);    
}

/**
*/
void 
Stats::setStat(const long cid, const CVariant& crv){
  TMapVariantIt it = _mstats.find( cid);
  if ( it != _mstats.end()){
    (*it).second = crv;
  }      
}

/**
*/
CVariant& 
Stats::getStat(const long cid){
  TMapVariantIt it = _mstats.find( cid);
  if ( it != _mstats.end()){
    return (*it).second;
  }
  throw "Stat not found";
}

const CVariant& 
Stats::getStat(const long cid) const {
  TMapVariantCIt it = _mstats.find( cid);
  if ( it != _mstats.end()){
    return (*it).second;
  }
  throw "Stat not found";
}

/**
*/
std::string 
Stats::toString() const{
  std::ostringstream out;
  TMapVariantCIt it = _mstats.begin();
  for(; it != _mstats.end(); it++){
    out<<"["<<(*it).first<<"]={"<<(*it).second<<"}"<<std::endl;
  }
  return out.str();
}

/**
*/
Component::Type
Character::TYPE = CHARACTER_TYPE;

Character::Character(const string &name, const unsigned long id, long lt):
  Component(TYPE), _id( id), _name( name), _lifeThreshold( lt)
{ 
  // Mandatory stats
  _stats.addStat( HEALTH,         DEFAULT_MIN_STAT);
  _stats.addStat( DAMAGE,         DEFAULT_MIN_STAT);
  _stats.addStat( ARMOR_CLASS,    DEFAULT_MIN_STAT);
  _stats.addStat( INITIATIVE,     DEFAULT_MIN_STAT);
}

Character::Character(const Character &ch):
Component(TYPE), _id( ch._id), _name( ch._name), _lifeThreshold( ch._lifeThreshold)
{
  _stats.addStat(HEALTH,      ch.get( HEALTH));
  _stats.addStat(DAMAGE,      ch.get( DAMAGE));
  _stats.addStat(ARMOR_CLASS, ch.get( ARMOR_CLASS));
  _stats.addStat(INITIATIVE,  ch.get( INITIATIVE));
}

std::string 
Character::toString() const {
  return _stats.toString();
}

/**
*/
void change(Character& c, const unsigned long id, const CVariant& v, func f){
    CVariant &r = c.get( id);
    f(r, v);
}

void plusVar(CVariant& rl, const CVariant& rv){
    rl = rl + rv;
}

void minusVar(CVariant& rl, const CVariant& rv){
    rl = rl - rv;
}

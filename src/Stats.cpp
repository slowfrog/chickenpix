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

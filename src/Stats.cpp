#include <iostream>
#include "Stats.h"

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
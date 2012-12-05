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

#include <iostream>

// Very simple Variant object
class CVariant {
  friend std::ostream& operator<<( std::ostream &os , const CVariant& v);

  typedef enum{ eString, eLong, eDouble, eFloat, eUnknown } TypeOfValue;
  
public:
  // Contructor(s)
  CVariant():_kindOfValue( eUnknown){}
  CVariant( const long l):_kindOfValue( eLong), _lValue( l){}
  CVariant( const float f):_kindOfValue( eFloat), _fValue( f){}
  CVariant( const double d):_kindOfValue( eDouble), _dValue( d){}
  CVariant( const std::string &s):_kindOfValue( eString), _sValue( s){}
  // Destrcutor
  ~CVariant(){}
  //Copy & affectation
  CVariant(const CVariant &rv)            { set(rv); }
  CVariant& operator=(const CVariant &rv) { 
    if ( _kindOfValue != rv._kindOfValue) throw "Bad type. Type mismatch!";
    set(rv); 
    return (*this);
  }
  
  // Caster(s)
  operator long()         { if ( eLong == _kindOfValue )   return _lValue; else throw "Bad type. Long expected!";}
  operator float()        { if ( eFloat == _kindOfValue )  return _fValue; else throw "Bad type. Float expected!";}
  operator double()       { if ( eDouble == _kindOfValue ) return _dValue; else throw "Bad type. Double expected!";}
  operator std::string()  { if ( eString == _kindOfValue ) return _sValue; else throw "Bad type. string expected!";}

  // +/- Operator(s)
  CVariant& operator+(const CVariant& rv){
      switch ( _kindOfValue) {
        case eLong:
            _lValue += rv._lValue;
            break;
        case eFloat:
            _fValue += rv._fValue;
            break;
        case eDouble:
            _dValue += rv._dValue;
            break;
        case eString:
            _sValue += rv._sValue;
            break;
        default:
            throw "Bad type. Unknown type!";
            break;
      }
      return (*this);
  }

  CVariant& operator-(const CVariant& rv){
      switch ( _kindOfValue) {
        case eLong:
            _lValue -= rv._lValue;
            break;
        case eFloat:
            _fValue -= rv._fValue;
            break;
        case eDouble:
            _dValue -= rv._dValue;
            break;
        case eString:            
            break;
        default:
            throw "Bad type. Unknown type!";
            break;
      }
      return (*this);
  }

  bool operator==(const CVariant& v) const {
      if ( _kindOfValue != v._kindOfValue ) return false;

      if (_kindOfValue == eLong )   return _lValue == v._lValue;
      if (_kindOfValue == eDouble ) return _dValue == v._dValue;
      if (_kindOfValue == eFloat )  return _fValue == v._fValue;;
      if (_kindOfValue == eString ) return _sValue == v._sValue;;

      return false;
  }

  bool operator<(const CVariant& v) const {
      if ( _kindOfValue != v._kindOfValue ) return false;

      if (_kindOfValue == eLong )   return _lValue < v._lValue;
      if (_kindOfValue == eDouble ) return _dValue < v._dValue;
      if (_kindOfValue == eFloat )  return _fValue < v._fValue;;
      if (_kindOfValue == eString ) return _sValue < v._sValue;;

      return false;
  }
  
  bool operator < (const long l) const {
      if (_kindOfValue == eLong )   return _lValue < l; 
      return false;
  }

  bool operator < (const double d) const {
      if (_kindOfValue == eDouble )   return _dValue < d; 
      return false;
  }

  bool operator < (const float f) const {
      if (_kindOfValue == eFloat )   return _fValue < f; 
      return false;
  }

  bool operator < (const std::string& s) const {
      if (_kindOfValue == eString )   return _sValue < s; 
      return false;
  }

  template<typename T>
  bool operator<=(const T& l) const {
      return ( (*this) ==l || (*this) < l );
  }

  // Specific affectation
  CVariant& operator = (const long &rv){
    if ( _kindOfValue != eLong) throw "Bad type. Long expected!";
    _lValue = rv;
    return *this;
  }
  
  CVariant& operator = (const float &rv){
    if ( _kindOfValue != eFloat) throw "Bad type. Float expected!";
    _fValue = rv;
    return *this;
  }
  
  CVariant& operator = (const double &rv){
    if ( _kindOfValue != eDouble) throw "Bad type. Double expected!";
    _dValue = rv;
    return *this;
  }
  
  CVariant& operator = (const std::string &rv){
    if ( _kindOfValue != eString) throw "Bad type. String expected!";
    _sValue = rv;
    return *this;
  }  
  
protected:
  // 
  void set(const CVariant &rv){
    _kindOfValue = rv._kindOfValue;
    switch ( _kindOfValue) {
      case eLong:
        _lValue = rv._lValue;
        break;
      case eFloat:
        _fValue = rv._fValue;
        break;
      case eDouble:
        _dValue = rv._dValue;
        break;
      case eString:
        _sValue = rv._sValue;
        break;
      default:
        throw "Bad type. Unknown type!";
        break;
    }
  }
  
private:
  TypeOfValue _kindOfValue;
  long        _lValue;
  double      _dValue;
  float       _fValue;
  std::string _sValue;
};

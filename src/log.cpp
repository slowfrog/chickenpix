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
 
#include <stdio.h>
#include <stdarg.h>
#include "log.h"

/**
 */
ILog     *ILog::_mLog   = new CLogOutput;
LogLevel ILog::_mLevel  = LEVEL_NONE;

/**
 */
void 
ILog::setLogger( ILog* plog, const LogLevel lvl){
  if ( !plog) {
    throw "Unexpected log";
  }
  if ( _mLog){
    delete _mLog;
    _mLog = NULL;
  }
  
  _mLog   = plog;
  _mLevel = lvl;
}

/**
 */
void 
ILog::Log( const char* frmt, ...){
  char sBuffer[512];
  va_list Params;
  va_start( Params, frmt);
  vsprintf( sBuffer, frmt, Params);
  va_end( Params);
  // log msg
  _mLog->print( sBuffer);
}

void 
ILog::Log( const unsigned long line, const std::string& file, const char* frmt, ...){
  char sBuffer[512];
  va_list Params;
  va_start( Params, frmt);
  vsprintf( sBuffer, frmt, Params);
  va_end( Params);
  // log msg
  _mLog->print( line, file, sBuffer);
}

void 
ILog::Log(const std::string& msg) {
  _mLog->print( msg);
}

/**
 */
void 
CLogOutput::print( const std::string& msg){
  std::ostringstream out;
  out<< msg;
  std::cout<<out.str();
}

void 
CLogOutput::print( const unsigned long line, const std::string& file, const std::string& msg){
  std::ostringstream out;
  out<<file<<"("<<line<<"):"<<msg;
  std::cout<<out.str();
}

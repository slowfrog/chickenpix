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

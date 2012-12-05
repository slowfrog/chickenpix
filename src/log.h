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

#include <sstream>
#include <iostream>

// Macros
#define LOGLVL(LVL, FMT, ...) if ( LVL <= ILog::Level() ) ILog::Log( __LINE__, __FILE__, FMT, ##__VA_ARGS__)
#define LOG(FMT, ...)         ILog::Log( FMT, ##__VA_ARGS__)
#define LOG2                  (ILog::Log())
#define LOG2DBG               if ( LEVEL_DEBUG == ILog::Level() ) ILog::Log()
#define LOG2MAIN              if ( LEVEL_MAIN == ILog::Level() ) ILog::Log()
#define LOG2ERR               if ( LEVEL_DEBUG == ILog::Level() ) ILog::Log()<<__FILE__<<"("<<__LINE__<<"):"

// Forward
class CLogOutput;

// Types
typedef enum {
  LEVEL_NONE  =0,
  LEVEL_MAIN,
  LEVEL_DEBUG
} LogLevel;

/**
 Log Interface
*/
class ILog
{
public:
  // Destructor
  virtual ~ILog(){}
  
  // API
  static ILog& Log() { return *_mLog;}
  static LogLevel Level() { return _mLevel;}
  static void setLevel( const LogLevel lvl ) { _mLevel = lvl;}
  static void setLogger(ILog* plog, const LogLevel lvl = LEVEL_NONE);
  static void Log(const unsigned long, const std::string&, const char*, ...);
  static void Log(const char*, ...);
  static void Log(const std::string&);
  
  // Warning : do not use std::endl to return line in a message, use "\n"
  template <class T> 
  ILog& operator<<( const T& msg)
  {
    std::ostringstream out;
    out << msg;
    print( out.str());
    return Log();
  }
  
protected:
  virtual void print(const unsigned long, const std::string&, const std::string&) =0;
  virtual void print(const std::string&) =0;
  
private:
  static ILog     *_mLog;
  static LogLevel _mLevel;
};

/**
 std::output Log
 */
class CLogOutput : public ILog
{
protected:
  void print(const std::string&);
  void print(const unsigned long, const std::string&, const std::string& msg);
};
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
#include <string>
#include "Singleton.h"
#include "System.h"

// Forward
class Notification;
class System;

// Def callback on notification
typedef void (*TNotifFunc)( System*);

/* Notification */
class Notification {
  friend class NotificationCenter;
  typedef std::vector<System*>     TVecNotifier;
  typedef std::map<long, TNotifFunc>  TMapNotifFunc;

public:
  const std::string Name() const { return mName;}

protected:
  // Constructor / Destructor
  Notification( const std::string &name): mName(name){}
  ~Notification(){}

  void registerNotifier  ( System*, TNotifFunc);
  void unregisterNotifier( System*);
  void Notify();
  
private:
  std::string   mName;
  TVecNotifier  mVNotifier;
  TMapNotifFunc mMNotifFunc;
};

/* Notification management */
class NotificationCenter : public CSingleton<NotificationCenter>
{
  typedef std::vector<Notification*>     TVecNotification;
  
public:
  // Constructor / Destructor
  NotificationCenter(){}
  ~NotificationCenter();
  
  // API
  Notification* createNotification( const std::string&);
  Notification* getNotification( const std::string&);
  
  void registerNotification ( System*, const std::string&, TNotifFunc);
  void unregisterNotification ( System*, Notification*);
  void unregisterNotification ( System*, const std::string&);
  
  void Notify( const std::string&);
  
private:
  TVecNotification  mVNotification;
};

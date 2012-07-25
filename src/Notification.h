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

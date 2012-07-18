#pragma once

#include <map>
#include <vector>
#include <string>
#include "Singleton.h"

// Forward
class Notification;

/* Notifier interface */
class INotifier  {
public:
  virtual void apply( const Notification& ) =0;
  virtual const long getId() const =0;
};

/* Notification */
class Notification {
  friend class NotificationCenter;
  typedef std::vector<INotifier*> TVecNotifier;

public:
  const std::string Name() const { return mName;}

protected:
  // Constructor / Destructor
  Notification( const std::string &name): mName(name){}
  ~Notification(){}

  void registerNotifier  ( INotifier*);
  void unregisterNotifier( INotifier*);
  void Notify();
  
private:
  std::string   mName;
  TVecNotifier  mVNotifier;
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
  Notification* getNotification( const long);
  Notification* getNotification( const std::string&);
  
  void registerNotification   ( INotifier*, Notification*);
  void registerNotification   ( INotifier*, const std::string&);
  void unregisterNotification ( INotifier*, Notification*);
  void unregisterNotification ( INotifier*, const std::string&);
  
  void Notify( const std::string&);
  
private:
  TVecNotification  mVNotification;
};

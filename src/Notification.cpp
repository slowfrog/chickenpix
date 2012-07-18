#include "Notification.h"

/**********************************************
/* Notification
/**********************************************/
void 
Notification::registerNotifier( INotifier *n){
  // Check if notifier already exists
  TVecNotifier::iterator it =  mVNotifier.begin();
  while ( it != mVNotifier.end()) {
    if ( (*it)->getId() == n->getId())
      return;
    it++;
  }
  // else add it
  mVNotifier.push_back( n);
}

void 
Notification::unregisterNotifier( INotifier *n){
  TVecNotifier::iterator it =  mVNotifier.begin();
  while ( it != mVNotifier.end()) {
    if ( (*it)->getId() == n->getId()){
      mVNotifier.erase( it);
    }
  }
}

void 
Notification::Notify(){
  TVecNotifier::iterator it = mVNotifier.begin();
  while( it != mVNotifier.end() ){
    (*it)->apply( *this);
    it++;
  }
}

/**********************************************
/* NotificationCenter
/**********************************************/
// Destructor
NotificationCenter::~NotificationCenter(){
  TVecNotification::iterator it = mVNotification.begin();
  while( it != mVNotification.end()){
    Notification *n = (*it);
    mVNotification.erase(it);
    delete n;
    it++;
  }
}

// Instanciate Notification
Notification * 
NotificationCenter::createNotification( const std::string &name){
  // Check if notification exists
  Notification *n( NULL);
  if ( NULL == getNotification( name) ){
    // Add
    n = new Notification ( name);
    mVNotification.push_back( n);
  }
  return n;
}

Notification* 
NotificationCenter::getNotification( const std::string &name){
  TVecNotification::iterator it = mVNotification.begin();
  while ( it != mVNotification.end()) {
    if ( (*it)->Name() == name) {
      return (*it);
    }
  }
  return NULL;
}

// Register Notification
void
NotificationCenter::registerNotification( INotifier *n, Notification *e){
  if ( e && n) {
    e->registerNotifier( n);
  }
}

void
NotificationCenter::registerNotification( INotifier *n, const std::string& name){
  if ( n) {
    Notification *e = getNotification( name);
    if ( NULL == e) {
      e = createNotification( name);
    }
    
    if ( e){
      e->registerNotifier( n);
    }
  }
}

// Unregister Notification
void
NotificationCenter::unregisterNotification( INotifier *n, Notification *e){
  if ( e && n){
    e->unregisterNotifier( n);
  }
}

void 
NotificationCenter::unregisterNotification ( INotifier *n, const std::string &name){
  if ( n) {
    Notification *e = getNotification( name);
    if ( n){
      e->unregisterNotifier( n);
    }
  }
  
}

// Notify Notifier :)
void 
NotificationCenter::Notify( const std::string &name){
  Notification *e = getNotification( name);
  if ( e){
    e->Notify();
  }
}
#include "Notification.h"

/**********************************************/
/* Notification                               */
/**********************************************/
void 
Notification::registerNotifier( System *n, TNotifFunc f){
  // Check if notifier already exists
  TVecNotifier::iterator it =  mVNotifier.begin();
  while ( it != mVNotifier.end()) {
    if ( (*it)->getType() == n->getType())
      return;
    it++;
  }
  // else add it
  mVNotifier.push_back( n);
  mMNotifFunc.insert( std::make_pair( n->getType(), f));
}

void 
Notification::unregisterNotifier( System *n){
  TVecNotifier::iterator it =  mVNotifier.begin();
  while ( it != mVNotifier.end()) {
    if ( (*it)->getType() == n->getType()){
      mVNotifier.erase( it);
    }
  }
  
  TMapNotifFunc::iterator itm = mMNotifFunc.find( n->getType());
  mMNotifFunc.erase( itm);
}

void 
Notification::Notify(){
  TVecNotifier::iterator it = mVNotifier.begin();
  while( it != mVNotifier.end() ){
    TMapNotifFunc::iterator itf = mMNotifFunc.find( (*it)->getType());
    if ( itf != mMNotifFunc.end() ){
      TNotifFunc f = itf->second;
      (itf->second)( (*it));
    }
    it++;
  }
}

/**********************************************/
/* NotificationCenter                         */
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
    it++;
  }
  return NULL;
}

// Register Notification
void 
NotificationCenter::registerNotification ( System *n, const std::string &name, TNotifFunc f){
  if ( n) {
    Notification *e = getNotification( name);
    if ( NULL == e) {
      e = createNotification( name);
    }
    
    if ( e){
      e->registerNotifier( n, f);
    }
  }
}

// Unregister Notification
void
NotificationCenter::unregisterNotification( System *n, Notification *e){
  if ( e && n){
    e->unregisterNotifier( n);
  }
}

void 
NotificationCenter::unregisterNotification ( System *n, const std::string &name){
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

#pragma once

// Headers
#include <map>
#include <queue>
#include <set>

#include "Resources.h"

// Constants
#define TAG_HERO        "HERO"
#define TAG_FOE         "FoeInFight"
#define TAG_RES_UI      "ResUI"

#define TAG_FIXED       "Fixed"
#define TAG_STATS       "StatsFight"
#define TAG_IMG         "Img"
#define TAG_NAME        "Name"

#define TAG_ATTACKER    "Attacker"
#define TAG_DEFENSER    "Defenser"

#define TAG_HEALTH      "Health"
#define TAG_DAMAGE      "Damage"
#define TAG_INITATIVE   "Initiative"
#define TAG_ARMOR       "Armor"

// Colors
#define HIGH_YELLOW     CPColor( 255, 255, 0, 255)
#define LIGHT_BROWN     CPColor( 200, 200, 128, 200)
#define LIGHT_RED       CPColor( 200, 128, 128, 200)

// Forward(s)
class EntityManager;
class Stats;
class Character;
class CVariant;
class Resource;

// Define type(s)
typedef enum { eText, eImage} eType;

typedef struct _sInfoRes{
  // Constructor for Text
  _sInfoRes( const std::string &txt, const std::string &f, const float x, const float y, const CPColor& c, bool highlight =false)
  :sType( eText), sText( txt), sResName( f), sX( x), sY( y), sColor( c), sHighLight( highlight){}
  // Constructor for Image
  _sInfoRes( const std::string &img, const float x, const float y, bool highlight =false)
  :sType( eImage), sResName( img), sX( x), sY( y), sColor( CPColor(0, 0, 0,0)), sHighLight( highlight){}
  // Properties
  eType       sType;
  std::string sText;
  std::string sResName;
  float       sX, sY;
  CPColor     sColor;
  bool        sHighLight;
} sInfoRs;

typedef std::vector<sInfoRs>           TVecRes;
typedef std::map<std::string, sInfoRs> TMapTagRes;

/**************************************************************/
/* UIEngine                                                  */
/**************************************************************/
class UIEngine {
public:
  // Constructor/Destructor
  UIEngine():mRes(NULL){}
  ~UIEngine(){}
  
  // Accessor
  void setResources( Resources*);
  
  // API
  void buildText(Entity             *, 
                 const std::string  &, 
                 const std::string  &,
                 const CPColor      &,
                 const float        , 
                 const float        
                 );
  void buildImg (Entity             *, 
                 const std::string  &, 
                 const float        , 
                 const float
                 );
  
private:
  Resources *mRes;
};

/**************************************************************/
/* IUIPart                                                   */
/**************************************************************/
class IUIPart{
public:
  // Constructor/Destructor
  IUIPart():mIsFirst( true), mDeltat( 0), mTheta( 0.), mTS( false){}
  virtual ~IUIPart(){}
  
  // Accessor
  inline bool isFirstCall() const { return mIsFirst;}
  inline bool isTimeShift() const { return mTS;}
  
  virtual  void reset() { mIsFirst = true; mTS = false;}
  
  // API
  virtual void refreshFixedPart ( EntityManager&, UIEngine*, int) =0;
  virtual void refreshPart      ( EntityManager&, UIEngine*, int) =0;
  
  // Common display treatment
  virtual void refresh( EntityManager& em, UIEngine *eng, int now){
    // Time shift
    mTS = false;
    if(now - mDeltat > 100){
      mDeltat = now;
      mTS     = true;
    }
    // Call refresh part panel
    if ( isFirstCall() ) {
      refreshFixedPart( em, eng, now);
      mIsFirst = false;
    }
    refreshPart( em, eng, now);
  }
  
protected:
  // Highlight
  int getAlpha( const int def);
  // Resource
  void buildResource( Entity*, UIEngine*, const sInfoRs&);
  
protected:
  // Time shift
  int   mDeltat;
  // Theta
  float mTheta;
  bool  mTS;
  
private:
  bool  mIsFirst; // watch dog
};

/**************************************************************/
/* UIStats                                                   */
/**************************************************************/
class UIStats: public IUIPart{
public:
  // Constructor/Destructor
  UIStats(): mAlpha( 0){}
  virtual ~UIStats(){}
  
  // API
  void addStatsFighters( const Character*, const bool);
  void updateStats     ( const Character*);
  void updateRole      ( const std::string&, const bool);
  
  void reset           ();
  void resetRes        ( EntityManager&);
  void infoStats       ( const std::string&, const bool, CPColor, const bool);
  
  // Interface
  virtual void refreshFixedPart ( EntityManager&, UIEngine*, int);
  virtual void refreshPart      ( EntityManager&, UIEngine*, int);
  
protected:
  void getStatsName( const long&, std::string&);
  
private:
  // Resources list attributes
  TVecRes     mStaticRes;
  TMapTagRes  mDynamicRes;
  // Effect
  int         mAlpha;
};

/**************************************************************/
/* UIConsole                                                 */
/**************************************************************/
class UIConsole: public IUIPart {
  typedef unsigned long             TPos;
  typedef std::vector<std::string>  TVecTxt;
public:
  // Constructor/Destructor
  UIConsole():mLastInserted( 0), mCur( 0), mSelected( 0){}
  ~UIConsole(){}
  
  //API
  inline bool empty() { return mVLines.empty();}
  void newLine            ( const std::string&);
  void buildDisplayedLine ();
  
  // Interface
  virtual void refreshFixedPart ( EntityManager&, UIEngine*, int);
  virtual void refreshPart      ( EntityManager&, UIEngine*, int);
  
  void reset() {IUIPart::reset(); mVLines.clear(); mDynamicRes.clear();}
  void resetRes( EntityManager&);
  
private:
  TVecTxt     mVLines;
  TMapTagRes  mDynamicRes;
  TPos        mLastInserted;
  TPos        mCur;
  TPos        mSelected;
};

/**************************************************************/
/* UIManager                                                 */
/**************************************************************/
// Manage visual part of system fight
class UIManager
{
public:
  // Constructor/Destructor
  UIManager( Resources*);
  ~UIManager(){}
  
  // API
  void refreshAll( EntityManager&, int);
  void resetAll( );
  void resetRes( EntityManager&);
  
  void addStats     ( const Character*, const bool);
  void updateStats  ( Character*, const bool);
  void displayRole  ( const std::string&, const bool);
  void displayInfo  ( const std::string&, const bool, CPColor, const int = 0);
  void consoleInfo  ( const std::string&);
  
private:
  // UI engine
  UIEngine    mUIEngine;
  // UI part
  UIStats    mGUIStats;
  UIConsole  mGUIConsole;
  // Resoures
  Resources   *mRes;
  // Effects
  int         mAlpha;
};

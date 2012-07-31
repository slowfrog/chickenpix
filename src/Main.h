#pragma once

#include <cassert>
#include "log.h"
#include "SystemFactory.h"
#include "SystemManager.h"
#include "InputState.h"
#include "TagEntityManager.h"
#include "HandleTransition.h"

// Prepare fight
void prepareFight( EntityManager&, CFightSystem*);
void checkFight( EntityManager&, CFightSystem*);

// Template function of the main game loop
template<class TimerClass>
void
runGame( CSystemFactory* pFac) {
  // init log
  ILog::setLogger( new CLogOutput, LEVEL_DEBUG);
  // Init
  //CTagEntityMng::get()->resetTagCollection();
  
  // Managers (entities)
  CSystemManager  SysMng;
  SysMng.createEntityManager( "Main");
  SysMng.createEntityManager( "Menu");
  SysMng.createEntityManager( "Fight");
  
  // Systems Main
  Render    *render     = pFac->createRender    ( "Render", 800, 600);
  assert( render);
  Sounds    *sounds     = pFac->createSounds    ( "Sounds");
  assert( sounds);
  Animation *anim       = pFac->createAnimation ( "Animation");
  assert( anim);
  Loader    *loader     = pFac->createLoader    ( "Loader",                   // System name
                                                  "resources/resources.xml",  // Resources
                                                  "resources/entities.xml",   // Entities desc
                                                  "beach"                     // Level name
                                                 );                   
  assert( loader);
  Inputs    *inputs     = pFac->createInputs    ( "MainInputs");
  assert( inputs);
  Scripting *scripting  = pFac->createScripting ( "Scripting");
  assert( scripting);
  Movement *movement    = pFac->createMovement  ( "Movement");
  assert( movement);
  // Register Sytem to manager
  SysMng.registerSystem( "Main", render);
  SysMng.registerSystem( "Main", sounds);
  SysMng.registerSystem( "Main", anim);
  SysMng.registerSystem( "Main", loader);
  SysMng.registerSystem( "Main", inputs);
  SysMng.registerSystem( "Main", scripting);
  SysMng.registerSystem( "Main", movement);
  // Call init on all system for "Main"
  SysMng.SystemInit   ( SysMng.getByName( "Main"));
  
  // Systems Menu
  Loader *loaderMenu  = pFac->createLoader( "LMenu",
                                            "resources/resources.xml",     // Resources (repeat)
                                            "resources/menu_entities.xml", // Entities desc
                                            ""                             // Level name
                                          ); 
  assert( loaderMenu);
  Inputs  *inputsMenu = pFac->createInputs    ( "MenuInputs");
  assert( inputsMenu);
  // Register system tp manager
  SysMng.registerSystem( "Menu", render);
  SysMng.registerSystem( "Menu", loaderMenu);
  SysMng.registerSystem( "Menu", inputsMenu);
  SysMng.registerSystem( "Menu", scripting);
  SysMng.registerSystem( "Menu", movement);
  // Call init on all system for "Menu"
  SysMng.SystemInit   ( SysMng.getByName( "Menu"));
  
  // System Fight
  Loader *loaderFight  = pFac->createLoader( "LFight",
                                             "resources/resources.xml",     // Resources (repeat)
                                             "resources/fight_entities.xml", // Entities desc
                                             ""                             // Level name
                                           ); 
  assert( loaderFight);
  CFightSystem  *fight  = pFac->createFightSystem( "FightRound");
  assert( fight);
  // Register system tp manager
  SysMng.registerSystem( "Fight", render);
  SysMng.registerSystem( "Fight", loaderFight);
  SysMng.registerSystem( "Fight", inputs);
  SysMng.registerSystem( "Fight", fight);
  // Call init on all system for "Menu"
  SysMng.SystemInit   ( SysMng.getByName( "Fight"));

  // Set current at starting
  SysMng.setCurrent( "Menu");
  cout << "Menu "<<SysMng.getByName( "Menu").toString() << endl;
  cout << "Main "<<SysMng.getByName( "Main").toString() << endl;
  std::string NextMode("Main");

  TimerClass timer;
  int prev = timer.getTime();

  // One step
  while (true) {
    int now = timer.getTime();

    // Process inputs
    SysMng.SystemUpdate( SysMng.getByRef(), now);
    if (SysMng.exitRequested()) {
      break;
    }
    
    if ( SysMng.getByRef().switchRequired() ){
      LOG2<<"Switch to :"<< SysMng.getByRef().requiredName()<<"\n";
      // Prepare switch
      HandleTransition ht;
      std::string nm = SysMng.getByRef().requiredName();
      
      if ( SysMng.getByRef().getName() == "Fight" && SysMng.getByRef().requiredName() == "Main") {
        fight->updateStats( SysMng.getByName( "Main"), "FoeInFight");
        fight->updateStats( SysMng.getByName( "Main"), "HERO", true);
      }
      
      ht.transit(SysMng.getByRef(), SysMng.getByName( nm), "HERO", true);
      if ( SysMng.getByRef().requiredName() == "Fight") {
        ht.transit(SysMng.getByRef(), SysMng.getByName( nm), "FoeInFight");
        // Switch mode
        SysMng.setCurrent( SysMng.getByRef().requiredName());
        // Prepare fight if needed
        prepareFight( SysMng.getByRef(), fight);
      }
      else{
        // Switch mode
        SysMng.setCurrent( SysMng.getByRef().requiredName());
        checkFight( SysMng.getByRef(), fight); 
      }
      
      if ( SysMng.getByRef().getName() == "Main" ) {
        SysMng.getByRef().getTagMng().unregisterTag( "FoeInFight");
      }
    }
    
    prev = now;
        
    // Do ~60FPS
    int sleepTime = 15 - (timer.getTime() - now);
    if (sleepTime < 0) {
      sleepTime = 0;
    }
    timer.sleep(sleepTime);
  }

  SysMng.SystemExit( SysMng.getByName( "Menu"));
  SysMng.SystemExit( SysMng.getByName( "Main"));
  SysMng.SystemExit( SysMng.getByName( "Fight"));
    
  // At this step all pointers still valids
  // delete them
  delete render;
  delete anim;
  delete loader;
  delete inputs;
  delete scripting;
  delete movement;
};

#pragma once

#include <cassert>
#include "log.h"
#include "SystemFactory.h"
#include "TagEntityManager.h"


// Template function of the main game loop
template<class TimerClass>
void
runGame( CSystemFactory* pFac) {
  // init log
  ILog::setLogger( new CLogOutput, LEVEL_DEBUG);
  // Init
  CTagEntityMng::get()->resetTagCollection();
  EntityManager em("Main");
  
  /*RenderClass render("Render", em, 800, 600);
  render.init();
  Animation anim("Animation", em);
  anim.init();
  LoaderClass loader("Loader", em, "resources/resources.xml");
  loader.setEntitiesDesc( "resources/entities.xml");
  loader.init();
  InputsClass inputs("Inputs", em);
  inputs.init();
  Scripting scripting("Scripting", em);
  scripting.init();
  Movement movement("Movement", em);
  movement.init();
   */
  
  Render    *render     = pFac->createRender    ( em, "Render", 800, 600);
  assert( render);
  Animation *anim       = pFac->createAnimation ( em, "Animation");
  assert( anim);
  Loader    *loader     = pFac->createLoader    ( em, "Loader", "resources/resources.xml", "resources/entities.xml");
  assert( loader);
  Inputs    *inputs     = pFac->createInputs    ( em, "Inputs");
  assert( inputs);
  Scripting *scripting   = pFac->createScripting( em, "Scripting");
  assert( scripting);
  Movement *movement    = pFac->createMovement  ( em, "Movement");
  assert( movement);
  
  // !!!AIE!!! l odre des system a l air important, il faudrait du coup prevoir un ordre d init ....
  render->init();
  anim->init();
  loader->init();
  inputs->init();
  scripting->init();
  movement->init();

  cout << em.toString() << endl;

  TimerClass timer;
  int prev = timer.getTime();

  // One step
  while (true) {
    int now = timer.getTime();

    // Process inputs
    inputs->update(now);
    if (inputs->isExitRequested()) {
      break;
    }

    // Execute scripts
    scripting->update(now);
    // "Physics" engine
    movement->update(now);
    // Update animations
    anim->update(now);
    // Render update
    render->update(now);
        
    prev = now;
        
    // Do ~60FPS
    int sleepTime = 15 - (timer.getTime() - now);
    if (sleepTime < 0) {
      sleepTime = 0;
    }
    timer.sleep(sleepTime);
  }

  movement->exit();
  scripting->exit();
  inputs->exit();
  loader->exit();
  render->exit();
  anim->exit();
  
  // At this step all pointers still valids
  // delete them
  delete render;
  delete anim;
  delete loader;
  delete inputs;
  delete scripting;
  delete movement;
};

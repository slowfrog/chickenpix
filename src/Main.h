#pragma once

#include "log.h"
#include "TagEntityManager.h"

// Template function of the main game loop
template<class RenderClass, class InputsClass, class LoaderClass, class TimerClass>
void
runGame() {
  // init log
  ILog::setLogger( new CLogOutput, LEVEL_DEBUG);
  // Init
  CTagEntityMng::get()->resetTagCollection();
  EntityManager em("Main");
  RenderClass render("Render", em, 800, 600);
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

  cout << em.toString() << endl;

  TimerClass timer;
  int prev = timer.getTime();

  // One step
  while (true) {
    int now = timer.getTime();

    // Process inputs
    inputs.update(now);
    if (inputs.isExitRequested()) {
      break;
    }

    // Execute scripts
    scripting.update(now);
    // "Physics" engine
    movement.update(now);
    // Update animations
    anim.update(now);
    // Render update
    render.update(now);
        
    prev = now;
        
    // Do ~60FPS
    int sleepTime = 15 - (timer.getTime() - now);
    if (sleepTime < 0) {
      sleepTime = 0;
    }
    timer.sleep(sleepTime);
  }

  movement.exit();
  scripting.exit();
  inputs.exit();
  loader.exit();
  render.exit();
  anim.exit();
};

#include "CL.h"

#include "../EntityManager.h"
#include "ClanLib.h"
#include "CLRender.h"
#include "CLLoader.h"
#include "CLResources.h"
#include "CLInputs.h"
#include "../Animation.h"
#include "../Scripting.h"

class DisplayProgram
{
public:
  static int main(const std::vector<CL_String> &args)
  {
    try
    {
      // Init
      EntityManager em("CL-main");
      ClanLib clanlib("ClanLib", em);
      clanlib.init();
      CLRender clrender("CLRender", em);
      clrender.init();
      Animation anim("Animation", em);
      anim.init();
      CLLoader clloader("Loader", em, "resources/resources.xml");
      clloader.init();
      CLInputs clinputs("Inputs", em);
      clinputs.init();
      Scripting scripting("Scripting", em);
      scripting.init();

      cout << em.toString() << endl;
      
      int prev = CL_System::get_time();

      // One step
      while (true) {
        int now = CL_System::get_time();

        // Process inputs
        clinputs.update(now);
        if (clinputs.isExitRequested()) {
          break;
        }

        // Execute scripts
        scripting.update(now);
        // Update animations
        anim.update(now);
        // Render update
        clrender.update(now);
        
        prev = now;
        
        // Do ~60FPS
        CL_System::sleep(15);
      }

      scripting.exit();
      clinputs.exit();
      clloader.exit();
      clrender.exit();
      anim.exit();
      clanlib.exit();
    }
    catch(CL_Exception &exception)
    {
      // Create a console window for text-output if not available
      CL_ConsoleWindow console("Console", 80, 160);
      CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
      console.display_close_message();
 
    }

    return 0;
  }
};
// Create global application object, you MUST include this line or the application start-up will fail to locate your application object.
CL_ClanApplication app(&DisplayProgram::main);

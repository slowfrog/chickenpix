#include <cassert>

#include "CL.h"

#include "../EntityManager.h"
//#include "ClanLib.h"
#include "CLSystemFactory.h"
#include "CLRender.h"
#include "CLLoader.h"
#include "CLResources.h"
#include "CLInputs.h"
#include "../Animation.h"
#include "../Scripting.h"
#include "../Movement.h"
#include "../Main.h"

// Interface to ClanLib timing system
class CLTimer {
public:
  int getTime() {
    return CL_System::get_time();
  }
  void sleep(int time) {
    CL_System::sleep(time);
  }
};

class DisplayProgram
{
public:
  static int main(const std::vector<CL_String> &args)
  {
    CLSystemFactory *pCLFactory(NULL);
    try
    {
      CL_SetupCore setupCore;
      CL_SetupDisplay setupDisplay;
      CL_SetupSWRender setupSWRender;
      CL_SetupSound setupSound;
      CL_SetupVorbis setupVorbis;

      // Direct music playing
      CL_SoundOutput output(44100);
      
      pCLFactory = new CLSystemFactory;
      assert( pCLFactory );
      runGame<CLTimer>( pCLFactory);
    }
    catch(CL_Exception &exception)
    {
      // Create a console window for text-output if not available
      CL_ConsoleWindow console("Console", 80, 160);
      CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
      console.display_close_message();
 
    }
    
    // Delete unused pointer(s)
    if ( pCLFactory ){
      delete pCLFactory;
    }

    return 0;
  }
};
// Create global application object, you MUST include this line or the application start-up will fail to locate your application object.
CL_ClanApplication app(&DisplayProgram::main);

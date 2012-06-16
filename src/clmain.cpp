#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/swrender.h>
#include <ClanLib/application.h>

#include "EntityManager.h"
#include "ClanLib.h"
#include "CLRender.h"
#include "CLLoader.h"
#include "CLSprites.h"

class DisplayProgram
{
public:
  static int main(const std::vector<CL_String> &args)
  {
    try
    {
      // Init
      EntityManager em("main");
      ClanLib clanlib("ClanLib", em);
      clanlib.init();
      CLRender clrender("CLRender", em);
      clrender.init();
      CLLoader clloader("Loader", em);
      clloader.init();

      cout << em.toString() << endl;
      
      // Those should go in the CLRender System
      CL_DisplayWindow &window = *(clrender.window);
      CL_GraphicContext &gc = window.get_gc();
      
      CL_InputDevice keyboard = window.get_ic().get_keyboard();
      CL_Font font(gc, "Tahoma", 50);
      CL_Font fontSmall(gc, "Tahoma", 12);

      CLSprites *ss = em.getComponent<CLSprites>();
      CL_Sprite *walkLeftSprite = ss->getSprite("walk_left");
      CL_Sprite *walkRightSprite = ss->getSprite("walk_right");
      CL_Sprite *curSpritePtr = walkRightSprite;
 
      CL_Rect ground(0, 280, 640, 480);
      float x = 300.0;
      float x_speed = 43.0; // pixels/s
      int prev = CL_System::get_time();



      // One step
      while (true) {
        int now = CL_System::get_time();
        // TODO update Inputs system
        bool escape_down = keyboard.get_keycode(CL_KEY_ESCAPE);
        if (escape_down) {
          break;
        }
        // Read messages from the windowing system message queue, if any are available:
        CL_KeepAlive::process();


        // Render update
        clrender.update(now);

        font.draw_text(gc, 100, 120, "Chickenpix!", CL_Colorf(1.0f, 0.0f, 0.0, 0.0f));

        CL_Sprite &curSprite = *curSpritePtr;
        curSprite.draw(gc, x, 222.0f);
        curSprite.update();
        
        int cur = CL_System::get_time();
        float dx = (cur - prev) * x_speed / 1000;
        prev = cur;
        x += dx;

        if (x > 580) {
          x_speed = -x_speed;
          curSpritePtr = walkLeftSprite;
        } else if (x < 20) {
          x_speed = -x_speed;
          curSpritePtr = walkRightSprite;
        }

        fontSmall.draw_text(gc, 5, 10, "Press [ESC] to exit...", CL_Colorf::white);
 
        // Make the stuff visible:
        window.flip();
 
 
        // Do ~60FPS
        CL_System::sleep(15);
      }
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

/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <array>         // for array

using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : ground(posUpperRight) 
   {
      lander.reset(posUpperRight);
      
      for (Star& star : stars) {
         star.reset(posUpperRight.getX(), posUpperRight.getY());
      }
   }
   
   // Draw everything on the screen
   void draw(ogstream & gout)
   {
      
      // draw each star before drawing ground and lander
      for (auto& star : stars)
      {
         star.draw(gout);
      }
      
      ground.draw(gout);
      lander.draw(thrust, gout);
   }
   
   // Get the input from the Interface.
   void getInput(const Interface* pUI)
   {
      thrust.set(pUI);
   }
   
   // Move the lander.
   void moveLander()
   {
      Acceleration a = lander.input(thrust, -1.62); // gravity on the moon is -1.62 m/s^2
      lander.coast(a, .1); // Time is .1
   }
   
private:
   Ground ground;
   Lander lander;
   Thrust thrust;
   array<Star, 50> stars;
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator * pSimulator = (Simulator *)p;

   ogstream gout;

   // Get input
   pSimulator->getInput(pUI);
   
   // move the lander
   pSimulator->moveLander();
   
   // draw everything
   pSimulator->draw(gout);
   
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();

   
   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}

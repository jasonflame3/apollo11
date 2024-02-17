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
#include <iomanip>       // for fixed and setprecision
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
      this->posUpperRight = posUpperRight;
      reset();
   }
   
   // Draw everything on the screen
   void draw(ogstream & gout, const Thrust & thrust)
   {
      
      // draw each star before drawing ground and lander
      for (auto& star : stars)
      {
         star.draw(gout);
      }
      
      ground.draw(gout);
      lander.draw(thrust, gout);

      //draw pilot info bottom left so it soesn't get in the way of the lander
      Position textPosition(10.0,40.0);
      gout.setPosition(textPosition);
      gout << "fuel:      " << lander.getFuel() << " lbs" << endl
            <<"altitude: " << int(ground.getElevation(lander.getPosition())) << " meters" << endl
            <<"speed:   " << fixed << setprecision(2) << lander.getSpeed() << " m/s";

      //draw the outcome text.
      if (lander.isFlying() == false) 
      {
         Position textResult( posUpperRight.getX() / 4.0 , posUpperRight.getY() / 3.0);
         gout.setPosition(textResult);

         if (lander.isDead())
         {
            gout << "You died in the cold heart of space." << endl;
         }
         else
         {
            assert(lander.isLanded());
            gout << "The eagle has landed." << endl;
         }
      }
   }
   
   
   // Move the lander.
   void moveLander(const Thrust & thrust)
   {
      Acceleration a = lander.input(thrust, -1.62); // gravity on the moon is -1.62 m/s^2
      lander.coast(a, .1); // Time for each frame is .1
   }
   
   // Set the star position and phase
   void setStars()
   {
      for (Star& star : stars) {
         star.reset(posUpperRight.getX(), posUpperRight.getY());
      }
   }
   
   // Reset lander ground and stars
   void reset()
   {
      ground.reset();
      lander.reset(posUpperRight);
      setStars();
   }
   
   // Check if the lander hits the ground or lands
   void detectCollisions()
   {
      if (ground.hitGround(lander.getPosition(), lander.getWidth()))
      {
         lander.crash();
      }
      // Cannot land when faster than max speed
      if (ground.onPlatform(lander.getPosition(), lander.getWidth()) && lander.getSpeed() <= lander.getMaxSpeed())
      {
         lander.land();
      }
   }
   
private:
   Position posUpperRight;
   Ground ground;
   Lander lander;
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

   Thrust thrust;
   thrust.set(pUI);
   
   if (pUI->isSpace())
   {
      pSimulator->reset();
   }
   
   // move the lander
   pSimulator->moveLander(thrust);
   
   // detect collision
   pSimulator->detectCollisions();
   
   // draw everything
   pSimulator->draw(gout,thrust);
   
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

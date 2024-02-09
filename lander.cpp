/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   status = PLAYING;
   angle.setUp();
   fuel = 5000.0;
   velocity.setDX(random(-10.0,-4.0));
   velocity.setDY(random(-2.0, 2.0));
   pos.setX(posUpperRight.getX()-1);
   pos.setY(random(posUpperRight.getY()*0.75, posUpperRight.getY() * 0.95));
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
   gout.drawLander(pos, angle.getRadians());
   gout.drawLanderFlames(pos, angle.getRadians(), thrust.isMain(), thrust.isClock(), thrust.isCounter());

   if (status == DEAD)
   {
      gout.drawLanderFlames(pos, angle.getRadians(),true, true, true);
   }

}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   double localThrust = 0.0;
   angle.add(thrust.rotation());
   if (thrust.isClock() && fuel >= 1.0)
   {
      fuel-=1.0;
   }
   if (thrust.isCounter() && fuel >= 1.0)
   {
      fuel-=1.0;
   }
   if (thrust.isMain() && fuel >= 10.0)
   {
      fuel -= 10.0;
      localThrust = thrust.mainEngineThrust();
   }
   Acceleration a;
   a.set(angle, localThrust);
   a.addDDY(gravity);
   return a;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   pos.add(acceleration, velocity, time);
   velocity.add(acceleration, time);
}

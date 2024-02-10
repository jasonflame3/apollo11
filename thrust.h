/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich, jason Chandler Tyler Lefevre
 * Summary:
 *    down, clockwise, and counterclockwise
 * 
 *    ticket 1: 45 minuites
 *    ticket 2: 21 minuites
 *    ticket 3: 10 minuites
 *    ticket 4: 25 minuites
 *    ticket 5: 1.5 hours
 *    ticket 6: 30 minutes
 *    ticket 7: 10 minutes
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface

class TestLander;
class TestThrust;

 /*****************************************************
  * THRUST
  * Represents activation of thrusters
  *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;
   
public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per second
   double rotation() const
   {
      double rotation = 0;
      if (clockwise)
      {
         rotation += 0.1;
      }
      
      if (counterClockwise)
      {
         rotation -= 0.1;
      }
      
      return rotation;
   }

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const
   {
      if (mainEngine)
      {
         return 45000.0 / 15103.0;
      }
      else
      {
         return 0;
      }
   }

   // reflect what is firing
   bool isMain()    const { return mainEngine;       }
   bool isClock()   const { return clockwise;        }
   bool isCounter() const { return counterClockwise; }

   // set the thrusters
   void set(const Interface * pUI)
   {
      mainEngine       = pUI->isDown();
      clockwise        = pUI->isLeft();
      counterClockwise = pUI->isRight();
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};

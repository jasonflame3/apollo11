/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/ 

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()
#include <assert.h> // for asserts
/*********************************************
 * VELOCITY : ADD
 *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
   dx += acceleration.getDDX() * time;
   dy += acceleration.getDDY() * time;
}

/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *********************************************/
double Velocity::getSpeed() const
{
   double speed = sqrt(dx * dx + dy * dy);
   assert(speed >= 0.0);
   return speed;
}

/*********************************************
 * VELOCITY : SET
 *  set from angle and direction
 *********************************************/
void Velocity::set(const Angle & angle, double magnitude)
{
   assert(magnitude >= 0.0); 
   dx = sin(angle.getRadians()) * magnitude;
   dy = cos(angle.getRadians()) * magnitude;
}

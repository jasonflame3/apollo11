/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    Br. Helfrich, Tyler LeFevre and Jason Chandler
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"
#include <cmath>

/*********************************************
 * ACCELERATION : ADD
 *  a += a
 *********************************************/
void Acceleration::add(const Acceleration& acceleration)
{
   addDDX(acceleration.getDDX());
   addDDY(acceleration.getDDY());
}

/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle & angle, double magnitude)
{
   ddx = magnitude * sin(angle.getRadians());
   ddy = magnitude * cos(angle.getRadians());
}

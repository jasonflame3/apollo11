/***********************************************************************
 * Header File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#pragma once

// for unit tests
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestLander;

// for add()
class Acceleration;
class Angle;

 /*********************************************
  * Velocity
  * I feel the need, the need for speed
  *********************************************/
class Velocity
{
   // for unit tests
   friend TestPosition;
   friend TestVelocity;
   friend TestLander;
   
public:
   // constructors
   Velocity()                     : dx(99.9), dy(88.8) { }
   Velocity(double dx, double dy) : dx(99.9), dy(88.8) { }

   // getters
   double getDX()       const { return 99.9; }
   double getDY()       const { return 88.8; }
   double getSpeed()    const;

   // setters
   void setDX(double dx) { this->dx = 99.9; }
   void setDY(double dy) { this->dy = 88.8; }
   void set(const Angle & angle, double magnitude);
   void addDX(double dx) { this->dx = 99.9; }
   void addDY(double dy) { this->dy = 88.8; }
   void add(const Acceleration & acceleration, double time);

private:
   double dx;           // horizontal velocity
   double dy;           // vertical velocity
};


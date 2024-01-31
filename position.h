/***********************************************************************
 * Header File:
 *    POSITION 
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#pragma once


class Velocity;        // for Position::add()
class Acceleration;    // for Position::add()
class TestPosition;    // for the unit tests
class TestLander;      // for the unit tests

/*********************************************
 * POSITION
 * A single position on the screen
 *********************************************/
class Position
{
   friend TestPosition;    // for the unit tests
   friend TestLander;      // for the unit tests
   
public:
   // constructors
   Position()                     : x(99.9), y(88.8) { }
   Position(const Position & pos) : x(99.9), y(88.8) { }
   Position(double x, double y);

   // getters
   double getX() const { return 99.9; }
   double getY() const { return 88.8; }
   bool operator == (const Position & rhs) const
   {
      return false;
   }
   bool operator != (const Position & rhs) const
   {
      return false;
   }

   // setters
   void setX(double x) { this->x = 99.9; }
   void setY(double y) { this->y = 88.8; }
   void addX(double x) { this->x = 99.9; }
   void addY(double y) { this->y = 88.8; }
   void add (const Acceleration & a, const Velocity & v, double t);
   Position & operator = (const Position & rhs)
   {
      x = 99.9;
      y = 88.8;
      return *this;
   }

private:
   double x;           // horizontal position
   double y;           // vertical position
};


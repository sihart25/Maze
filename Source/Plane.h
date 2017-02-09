//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Plane.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Plane_h
#define Plane_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
#include "Group.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Plane : public Shape {

    public:

        Plane() : _width(1.0), _height(1.0), _left(0.0), _right(1.0), _bottom(0.0), _top(1.0) {}
        Plane(const Material &material, const Vectors &centre, double width, double height) : Shape(material, centre), _width(width), _height(height) {}
        virtual Node *clone() const { return new Plane(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;

    private:

        virtual void write(ostream &out) const { cout << "Plane" << endl; Shape::write(out); }

        double _width;
        double _height;
        double _left;
        double _right;
        double _bottom;
        double _top;

    };

} // ComputerGraphics

#endif // Plane_h

//------------------------------------------------------------------------------

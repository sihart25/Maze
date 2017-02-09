//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Cylinder.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Cylinder_h
#define Cylinder_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
#include "Group.h"
#include "Vectors.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Cylinder : public Shape {

    public:

        Cylinder() : _radius(1.0), _height(1.0), _top(true), _bottom(true) {}
        virtual Node *clone() const { return new Cylinder(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;

    private:

        virtual void write(ostream &out) const { cout << "Cylinder" << endl; Shape::write(out); }

        double _radius;
        double _height;
        bool _top;
        bool _bottom;

    };

} // ComputerGraphics

#endif // Cylinder_h

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Sphere.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Sphere_h
#define Sphere_h

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

    class Sphere : public Shape {

    public:

        Sphere() : _radius(1.0) {}
        virtual Node *clone() const { return new Sphere(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;

    private:

        virtual void write(ostream &out) const { cout << "Sphere" << endl; Shape::write(out); }

        double _radius;

    };

} // ComputerGraphics

#endif // Sphere_h

//------------------------------------------------------------------------------

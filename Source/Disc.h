//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Disc.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Disc_h
#define Disc_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
#include "Material.h"
#include "Vectors.h"
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

    class Disc : public Shape {

    public:

        Disc() : _radius(1.0), _inside(false) {}
        Disc(const Material &material, const Vectors &centre,
            double radius, bool inside) : Shape(material, centre), _radius(radius), _inside(inside) {}
        virtual Node *clone() const { return new Disc(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;

    private:

        virtual void write(ostream &out) const { cout << "Disc" << endl; Shape::write(out); }

        double _radius;
        bool _inside;

    };

} // ComputerGraphics

#endif // Disc_h

//------------------------------------------------------------------------------

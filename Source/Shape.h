//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Shape.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Shape_h
#define Shape_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Node.h"
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

    class Shape : public Node {

    public:

        Shape() : _centre(0.0, 0.0, 0.0, 1.0) {}
        Shape(const Material &material, const Vectors &centre) :
            _material(material), _centre(centre) {}
        virtual ~Shape() {}
        virtual Node *clone() const { return new Shape(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const {}

    protected:

        virtual void write(ostream &out) const { cout << "Shape" << endl; }

        Material _material;
        Vectors _centre;

    };

} // ComputerGraphics

#endif // Shape_h

//------------------------------------------------------------------------------

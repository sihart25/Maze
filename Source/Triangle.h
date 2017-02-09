//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Triangle.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Triangle_h
#define Triangle_h

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

    class Triangle : public Shape {

    public:

        Triangle() : _vertexA(-1.0, -1.0, 0.0, 1.0), _vertexB(1.0, -1.0, 0.0, 1.0),
            _vertexC(0.0, 1.0, 0.0, 1.0), _smooth(false) {}
        Triangle(const Material &material, const Vectors &centre,
            const Vectors &vA, const Vectors &vB, const Vectors &vC, bool smooth,
            const Vectors &nA, const Vectors &nB, const Vectors &nC) :
            Shape(material, centre), _vertexA(vA), _vertexB(vB), _vertexC(vC),
            _smooth(smooth), _normalA(nA), _normalB(nB), _normalC(nC) {}
        virtual Node *clone() const { return new Triangle(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;

    private:

        virtual Vectors normal(const Vectors &intersect) const;
        virtual void write(ostream &out) const { cout << "Triangle" << endl; Shape::write(out); }

        Vectors _vertexA;
        Vectors _vertexB;
        Vectors _vertexC;
        bool _smooth;
        Vectors _normalA;
        Vectors _normalB;
        Vectors _normalC;

    };

} // ComputerGraphics

#endif // Triangle_h

//------------------------------------------------------------------------------

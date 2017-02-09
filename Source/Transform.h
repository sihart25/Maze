//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Transform.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Transform_h
#define Transform_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Node.h"
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

    class Transform : public Node {

    public:

        Transform() : _translate(0.0, 0.0, 0.0), _axis(0.0, 0.0, 1.0), _angle(0.0), _spin(0.0),
            _scale(1.0, 1.0, 1.0) {}
        Transform(const Vectors &translate, const Vectors &axis, double angle, double spin, const Vectors &scale) :
            _translate(translate), _axis(axis), _angle(angle), _spin(spin), _scale(scale) {}
        virtual Node *clone() const { return new Transform(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;
        virtual void update();
        void translate(const Vectors &translate) {
            _translate = translate;
        }
        void axis(const Vectors &axis) {
            _axis = axis;
        }
        void angle(double angle) {
            _angle = angle;
        }
        void spin(double spin) {
            _spin = spin;
        }
        void scale(const Vectors &scale) {
            _scale = scale;
        }

    private:

        void spin(double &angle, double spin) const;
        virtual void write(ostream &out) const { out << "Transform" << endl; }

        Vectors _translate;
        Vectors _axis;
        mutable double _angle;
        double _spin;
        Vectors _scale;

    };

} // ComputerGraphics

#endif // Transform_h

//------------------------------------------------------------------------------

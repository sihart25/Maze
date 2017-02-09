//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Mesh.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Mesh_h
#define Mesh_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
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

    class Mesh : public Shape {

        //------------------------------------------------------------------------------
        // nested class definition

        class Face {

        public:

            Face() : _a(0), _b(0), _c(0) {}
            int a() const { return _a; }
            int b() const { return _b; }
            int c() const { return _c; }
            void normal(const Vectors &n) { _normal = n; }
            const Vectors &normal() const { return _normal; }
            friend istream &operator>>(istream &in, Face &f) {
                f.read(in);
                return in;
            }

        private:

            void read(istream &in) {
                in >> _a >> _b >> _c;
            }
            int _a;
            int _b;
            int _c;
            Vectors _normal;

        };

    //------------------------------------------------------------------------------
    // class definition

    public:

        Mesh() : _smooth(false) {
        }
        Mesh(const Mesh &mesh) : Shape(mesh) {
            copy(mesh);
        }
        Mesh &operator=(const Mesh &mesh) {
            if (this != &mesh) {
                Shape::operator=(mesh);
                erase();
                copy(mesh);
            }
            return *this;
        }
        ~Mesh() {
            erase();
        }
        virtual Node *clone() const { return new Mesh(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;

    private:

        void erase();
        void copy(const Mesh &mesh);
        bool readVertex(istream &in, string &token);
        bool readNormal(istream &in, string &token);
        bool readFace(istream &in, string &token);
        virtual void write(ostream &out) const { cout << "Mesh" << endl; Shape::write(out); }

        vector<Vectors *> _vertex;
        mutable vector<Vectors *> _normal;
        vector<Face *> _face;
        bool _smooth;

    };

} // ComputerGraphics

#endif // Mesh_h

//------------------------------------------------------------------------------

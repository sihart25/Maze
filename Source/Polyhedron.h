//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Polyhedron.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Polyhedron_h
#define Polyhedron_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Shape.h"
#include "Group.h"
#include "Light.h"
#include "Colour.h"
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

    class Polyhedron : public Shape {

        //------------------------------------------------------------------------------
        // nested class definition

        class Face {

        public:

            Face() : _numberOfIndices(0), _indices(0) {}
            Face(const Face &face) {
                copy(face);
            }
            Face &operator=(const Face &face) {
                if (this != &face) {
                    erase();
                    copy(face);
                }
                return *this;
            }
            ~Face() { erase(); }
            friend istream &operator>>(istream &in, Face &face) {
                face.read(in);
                return in;
            }
            int numberOfIndices() const { return _numberOfIndices; }
            const int *indices() const { return _indices; }

        private:

            void erase() {
                delete[] _indices;
            }
            void copy(const Face &face) {
                _numberOfIndices = face._numberOfIndices;
                _indices = new int[_numberOfIndices];
                for (int i = 0; i < _numberOfIndices; i++) {
                    _indices[i] = face._indices[i];
                }
            }
            void read(istream &in) {
                in >> _numberOfIndices;
                _indices = new int[_numberOfIndices];
                for (int i = 0; i < _numberOfIndices; i++) {
                    in >> _indices[i];
                }
            }

            int _numberOfIndices;
            int *_indices;

        };

    //------------------------------------------------------------------------------
    // class definition

    public:

        Polyhedron() : _radius(1.0), _numberOfVertices(0), _vertices(0), _numberOfFaces(0), _faces(0) {}
        Polyhedron(const Polyhedron &polyhedron) : Shape(polyhedron) {
            copy(polyhedron);
        }
        Polyhedron &operator=(const Polyhedron &polyhedron) {
            if (this != &polyhedron) {
                Polyhedron::operator=(polyhedron);
                erase();
                copy(polyhedron);
            }
            return *this;
        }
        ~Polyhedron() {
            erase();
        }
        virtual Node *clone() const { return new Polyhedron(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;

    private:

        void erase();
        void copy(const Polyhedron &polyhedron);
        void readFile(istream &in);
        void render(const Game &game, int face) const;
        Vectors normal(int face) const;
        void write(ostream &out) const { out << "Polyhedron" << endl; }

        double _radius;
        int _numberOfVertices;
        Vectors **_vertices;
        int _numberOfFaces;
        Face **_faces;
        string _filename;

    };

} // ComputerGraphics

#endif // Polyhedron_h

//------------------------------------------------------------------------------

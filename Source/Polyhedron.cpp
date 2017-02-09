//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Polyhedron.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Polyhedron.h"
#include "Group.h"
#include "Colour.h"
#include "Vectors.h"
#include "Reader.h"
#include "Material.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// erase polyhedron
void Polyhedron::erase() {
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; vertexIndex++) {
        delete _vertices[vertexIndex];
    }
    delete[] _vertices;
    for (int faceIndex = 0; faceIndex < _numberOfFaces; faceIndex++) {
        delete _faces[faceIndex];
    }
    delete[] _faces;
}

//------------------------------------------------------------------------------
// copy polyhedron
void Polyhedron::copy(const Polyhedron &polyhedron) {
    _radius = polyhedron._radius;
    _numberOfVertices = polyhedron._numberOfVertices;
    _numberOfFaces = polyhedron._numberOfFaces;
    _filename = polyhedron._filename;
    _vertices = new Vectors *[_numberOfVertices];
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        _vertices[vertexIndex] = new Vectors(*polyhedron._vertices[vertexIndex]);
    }
    _faces = new Face *[_numberOfFaces];
    for (int faceIndex = 0; faceIndex < _numberOfFaces; ++faceIndex) {
        _faces[faceIndex] = new Face(*polyhedron._faces[faceIndex]);
    }
}

//------------------------------------------------------------------------------
// read polyhedron
bool Polyhedron::read(istream &in, string &token, Group &group) {
    if (token == "Polyhedron") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing polyhedron opening brace");
        }
        in >> token;
        Polyhedron *polyhedron = new Polyhedron;
        group.push_back(polyhedron);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (polyhedron->_material.read(in, token)) {}
            else if (token == "Filename") {
                in >> polyhedron->_filename >> token;
            }
            else if (token == "Centre") {
                polyhedron->_centre.readPosition(in);
                in >> token;
            }
            else if (token == "Radius") {
                in >> polyhedron->_radius >> token;
            }
            else {
                throw string("Error : Invalid polyhedron attribute = " + token);
            }
        }
        in >> token;
        try {
            ifstream in(polyhedron->_filename.c_str());
            if (!in.good()) {
                throw string("Error : Invalid file name = " + polyhedron->_filename);
            }
            polyhedron->readFile(in);
        }
        catch (string s) {
            cout << s << endl;
        }
        catch (...) {
            cout << "Error : Unknown exception caught in read" << endl;
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read polyhedron file
void Polyhedron::readFile(istream &in) {
    in >> _numberOfVertices;
    _vertices = new Vectors *[_numberOfVertices];
    for (int vertexIndex = 0; vertexIndex < _numberOfVertices; ++vertexIndex) {
        // read into container of vertices
        _vertices[vertexIndex] = new Vectors();
        _vertices[vertexIndex]->readPosition(in);
    }
    in >> _numberOfFaces;
    _faces = new Face *[_numberOfFaces];
    for (int faceIndex = 0; faceIndex < _numberOfFaces; ++faceIndex) {
        // read into container of faces
        _faces[faceIndex] = new Face();
        in >> *_faces[faceIndex];
    }
}

//------------------------------------------------------------------------------
// render this polyhedron
void Polyhedron::render(const Game &game) const {
    for (int faceIndex = 0; faceIndex < _numberOfFaces; ++faceIndex) {
        render(game, faceIndex);
    }
}

//------------------------------------------------------------------------------
// render face of this polyhedron
void Polyhedron::render(const Game &game, int face) const {
    _material.render(game);
    glPushMatrix();
    glTranslated(_centre.x(), _centre.y(), _centre.z());
    glScaled(_radius, _radius, _radius);
    glBegin(GL_POLYGON);
    Vectors n(normal(face));
    glNormal3d(n(X), n(Y), n(Z));
    for (int index = 0; index < _faces[face]->numberOfIndices(); ++index) {
        Vectors vertex = *_vertices[_faces[face]->indices()[index]];
        glVertex3d(vertex.x(), vertex.y(), vertex.z());
    }
    glEnd();
    glPopMatrix();
}

//------------------------------------------------------------------------------
// normal to face of this polyhedron
Vectors Polyhedron::normal(int face) const {
    Vectors vertexA = *_vertices[_faces[face]->indices()[0]];
    Vectors vertexB = *_vertices[_faces[face]->indices()[1]];
    Vectors vertexC = *_vertices[_faces[face]->indices()[2]];
    Vectors ab(vertexB - vertexA);
    Vectors ac(vertexC - vertexA);
    Vectors direction(ab.cross(ac));
    return direction;
}

//------------------------------------------------------------------------------

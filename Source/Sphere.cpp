//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Sphere.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Sphere.h"
#include "Group.h"
#include "Reader.h"
#include "Vectors.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read sphere
bool Sphere::read(istream &in, string &token, Group &group) {
    if (token == "Sphere") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing sphere opening brace");
        }
        in >> token;
        Sphere *sphere = new Sphere();
        group.push_back(sphere);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (sphere->_material.read(in, token)) {}
            else if (token == "Radius") {
                in >> sphere->_radius >> token;
            }
            else if (token == "Centre") {
                sphere->_centre.readPosition(in);
                in >> token;
            }
            else {
                throw string("Error : Invalid sphere attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render sphere
void Sphere::render(const Game &game) const {
    _material.render(game);
    glPushMatrix();
    glTranslated(_centre.x(), _centre.y(), _centre.z());
    GLUquadricObj *sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, _radius, 20, 10);
    gluDeleteQuadric(sphere);
    glPopMatrix();
}

//------------------------------------------------------------------------------

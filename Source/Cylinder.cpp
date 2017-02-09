//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Cylinder.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Cylinder.h"
#include "Group.h"
#include "Reader.h"
#include "Disc.h"
#include "Vectors.h"
#include "Constants.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read cylinder
bool Cylinder::read(istream &in, string &token, Group &group) {
    if (token == "Cylinder") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing cylinder opening brace");
        }
        in >> token;
        Cylinder *cylinder = new Cylinder();
        group.push_back(cylinder);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (cylinder->_material.read(in, token)) {}
            else if (token == "Radius") {
                in >> cylinder->_radius >> token;
            }
            else if (token == "Height") {
                in >> cylinder->_height >> token;
            }
            else if (token == "Centre") {
                cylinder->_centre.readPosition(in);
                in >> token;
            }
            else if (token == "Top") {
                in /*>> boolalpha*/ >> cylinder->_top /*>> noboolalpha*/ >> token;
            }
            else if (token == "Bottom") {
                in /*>> boolalpha*/ >> cylinder->_bottom /*>> noboolalpha*/ >> token;
            }
            else {
                throw string("Error : Invalid cylinder attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render cylinder
void Cylinder::render(const Game &game) const {
    if (_top) {
        Disc disc = Disc(_material, _centre + Vectors(0.0, 0.0, _height), _radius, false);
        disc.render(game);
    }
    if (_bottom) {
        Disc disc = Disc(_material, _centre, _radius, true);
        disc.render(game);
    }
    _material.render(game);
    glPushMatrix();
    glTranslated(_centre.x(), _centre.y(), _centre.z());
    GLUquadricObj *cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluCylinder(cylinder, _radius, _radius, _height, 20, 5);
    gluDeleteQuadric(cylinder);
    glPopMatrix();
}

//------------------------------------------------------------------------------

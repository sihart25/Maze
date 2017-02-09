//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Disc.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Disc.h"
#include "Group.h"
#include "Reader.h"
#include "Constants.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read disc
bool Disc::read(istream &in, string &token, Group &group) {
    if (token == "Disc") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing disc opening brace");
        }
        in >> token;
        Disc *disc = new Disc();
        group.push_back(disc);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (disc->_material.read(in, token)) {}
            else if (token == "Radius") {
                in >> disc->_radius >> token;
            }
            else if (token == "Centre") {
                disc->_centre.readPosition(in);
                in >> token;
            }
            else {
                throw string("Error : Invalid disc attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render disc
void Disc::render(const Game &game) const {
    _material.render(game);
    glPushMatrix();
    glTranslated(_centre.x(), _centre.y(), _centre.z());
    GLUquadricObj *disc = gluNewQuadric();
    gluQuadricDrawStyle(disc, GLU_FILL);
    gluQuadricOrientation(disc, _inside ? GLU_INSIDE : GLU_OUTSIDE);
    gluQuadricNormals(disc, GLU_FLAT);
    gluDisk(disc, 0.0, _radius, 20, 5);
    gluDeleteQuadric(disc);
    glPopMatrix();
}

//------------------------------------------------------------------------------

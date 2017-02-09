//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Plane.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Plane.h"
#include "Group.h"
#include "Reader.h"
#include "Vectors.h"
#include "Constants.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read plane
bool Plane::read(istream &in, string &token, Group &group) {
    if (token == "Plane") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing plane opening brace");
        }
        in >> token;
        Plane *plane = new Plane();
        group.push_back(plane);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (plane->_material.read(in, token)) {}
            else if (token == "Width") {
                in >> plane->_width >> token;
            }
            else if (token == "Height") {
                in >> plane->_height >> token;
            }
            else if (token == "Centre") {
                plane->_centre.readPosition(in);
                in >> token;
            }
            else if (token == "Left") {
                in >> plane->_left >> token;
            }
            else if (token == "Right") {
                in >> plane->_right >> token;
            }
            else if (token == "Bottom") {
                in >> plane->_bottom >> token;
            }
            else if (token == "Top") {
                in >> plane->_top >> token;
            }
            else {
                throw string("Error : Invalid plane attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render plane
void Plane::render(const Game &game) const {
    _material.render(game);
    glPushMatrix();
    glTranslated(_centre.x(), _centre.y(), _centre.z());
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    glTexCoord2d(_left, _bottom);
    glVertex3d(-0.5 * _width, -0.5 * _height, 0.0);
    glTexCoord2d(_right, _bottom);
    glVertex3d(0.5 * _width, -0.5 * _height, 0.0);
    glTexCoord2d(_right, _top);
    glVertex3d(0.5 * _width, 0.5 * _height, 0.0);
    glTexCoord2d(_left, _top);
    glVertex3d(-0.5 * _width, 0.5 * _height, 0.0);
    glEnd();
    glPopMatrix();
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Light.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#pragma hdrstop
#include "Light.h"
#include "Group.h"
#include "Reader.h"
#include "Colour.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
int Light::_count = 0;

//------------------------------------------------------------------------------
// static function to read light
bool Light::read(istream &in, string &token, Group &group) {
    if (token == "Light") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing light opening brace");
        }
        in >> token;
        Light *light = new Light();
        group.push_back(light);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (token == "Centre") {
                light->_position.readPosition(in);
                in >> token;
            }
            else if (token == "Ambient") {
                in >> light->_ambient >> token;
            }
            else if (token == "Diffuse") {
                in >> light->_diffuse >> token;
            }
            else if (token == "Specular") {
                in >> light->_specular >> token;
            }
            else if (token == "Infinite") {
                in /*>> boolalpha*/ >> light->_infinite >> /*noboolalpha >>*/ token;
            }
            else {
                throw string("Error : Invalid light attribute = " + token);
            }
        }
        in >> token;
        if (light->_infinite) {
            light->_position.setDirection();
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render light
void Light::render(const Game &/*game*/) const {
    GLfloat position[DIM];
    GLfloat colour[COLOURS];
    glLightfv(GL_LIGHT[_count], GL_POSITION, _position.toGLfloat(position));
    glLightfv(GL_LIGHT[_count], GL_AMBIENT, _ambient.toGLfloat(colour));
    glLightfv(GL_LIGHT[_count], GL_DIFFUSE, _diffuse.toGLfloat(colour));
    glLightfv(GL_LIGHT[_count], GL_SPECULAR, _specular.toGLfloat(colour));
    glEnable(GL_LIGHT[_count]);
    if (_count == GL_LIGHT7) {
        _count = GL_LIGHT0;
    }
    else {
        ++_count;
    }
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Transform.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#pragma hdrstop
#include "Transform.h"
#include "Group.h"
#include "Reader.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read transform
bool Transform::read(istream &in, string &token, Group &group) {
    if (token == "Transform") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing transform opening brace");
        }
        in >> token;
        Transform *transform = new Transform();
        group.push_back(transform);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (token == "Translate") {
                transform->_translate.readDirection(in);
                in >> token;
            }
            else if (token == "Axis") {
                transform->_axis.readDirection(in);
                in >> token;
            }
            else if (token == "Angle") {
                in >> transform->_angle >> token;
            }
            else if (token == "Spin") {
                in >> transform->_spin >> token;
            }
            else if (token == "Scale") {
                transform->_scale.readDirection(in);
                in >> token;
            }
            else {
                throw string("Error : Invalid transform attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render this transform
void Transform::render(const Game &/*game*/) const {
    glTranslated(_translate.x(), _translate.y(), _translate.z());
    glRotated(_angle, _axis.x(), _axis.y(), _axis.z());
    glScaled(_scale.x(), _scale.y(), _scale.z());
}

//------------------------------------------------------------------------------
// update this transform
void Transform::update() {
    spin(_angle, _spin);
}

//------------------------------------------------------------------------------
// spin an angle
void Transform::spin(double &angle, double spin) const {
    angle += spin;
    angle -= 360.0 * floor(angle / 360.0);
}

//------------------------------------------------------------------------------

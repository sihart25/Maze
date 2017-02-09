//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Camera.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <GL/glut.h>
#pragma hdrstop
#include "Camera.h"
#include "Group.h"
#include "Game.h"
#include "Reader.h"
#include "Vectors.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read camera
bool Camera::read(istream &in, string &token, Group &group) {
    if (token == "Camera") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing camera opening brace");
        }
        in >> token;
        Camera *camera = new Camera();
        group.push_back(camera);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {
            }
            else if (token == "Position") {
                camera->_position.readPosition(in);
                in >> token;
            }
            else if (token == "Direction") {
                camera->_direction.readDirection(in);
                in >> token;
            }
            else if (token == "Up") {
                camera->_up.readDirection(in);
                in >> token;
            }
            else if (token == "FieldOfView") {
                in >> camera->_fieldOfView >> token;
            }
            else {
                throw string("Error : Invalid camera attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform by this camera
void Camera::render(const Game &game) const {

    const double nearClip = 0.01;
    const double farClip = 100.0;
    const double distance = 3.0;
    const double separation = 0.15;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double height = tan(_fieldOfView * 0.5 * PI / 180.0) * 2.0 * distance;
    double width = height * (double)glutGet(GLUT_WINDOW_WIDTH) / (double)glutGet(GLUT_WINDOW_HEIGHT);
    if ((game.key() == "LeftView") || (game.key() == "RightView")) {
        width *= 0.5;
    }

    double left;
    if (game.key() == "LeftView") {
        left = -separation * 0.5 - width;
    }
    else if (game.key() == "RightView") {
        left = separation * 0.5;
    }
    else {
        left = -width * 0.5;
    }
    double right = left + width;
    double bottom = -height * 0.5;
    double top = bottom + height;

    left *= nearClip / distance;
    right *= nearClip / distance;
    bottom *= nearClip / distance;
    top *= nearClip / distance;

    glFrustum(left, right, bottom, top, nearClip, farClip);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (game.key() == "LeftView") {
        glRotated((atan2(separation * 0.5 + width * 0.5, distance) - atan2(separation * 0.5, distance)) / PI * 180.0, 0.0, 1.0, 0.0);
        gluLookAt(separation * 0.5, 0.0, 0.0, 0.0, 0.0, -distance, 0.0, 1.0, 0.0);
    }
    else if (game.key() == "RightView") {
        glRotated(-(atan2(separation * 0.5 + width * 0.5, distance) - atan2(separation * 0.5, distance)) / PI * 180.0, 0.0, 1.0, 0.0);
        gluLookAt(-separation * 0.5, 0.0, 0.0, 0.0, 0.0, -distance, 0.0, 1.0, 0.0);
    }

    gluLookAt(_position.x(), _position.y(), _position.z(),
        _position.x() + _direction.x(), _position.y() + _direction.y(), _position.z() + _direction.z(),
        _up.x(), _up.y(), _up.z());
}

//------------------------------------------------------------------------------

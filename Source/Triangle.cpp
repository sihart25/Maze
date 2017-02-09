//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Triangle.cpp
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
#include "Triangle.h"
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
// static read triangle
bool Triangle::read(istream &in, string &token, Group &group) {
    if (token == "Triangle") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing triangle opening brace");
        }
        in >> token;
        Triangle *triangle = new Triangle();
        group.push_back(triangle);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (triangle->_material.read(in, token)) {}
            else if (token == "VertexA") {
                triangle->_vertexA.readPosition(in);
                in >> token;
            }
            else if (token == "VertexB") {
                triangle->_vertexB.readPosition(in);
                in >> token;
            }
            else if (token == "VertexC") {
                triangle->_vertexC.readPosition(in);
                in >> token;
            }
            else if (token == "Centre") {
                triangle->_centre.readPosition(in);
                in >> token;
            }
            else {
                throw string("Error : Invalid triangle attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render triangle
void Triangle::render(const Game &game) const {
    _material.render(game);
    glPushMatrix();
    glTranslated(_centre.x(), _centre.y(), _centre.z());
    glBegin(GL_TRIANGLES);
    if (_smooth) {
        glNormal3d(_normalA(X), _normalA(Y), _normalA(Z));
        glVertex3d(_vertexA(X), _vertexA(Y), _vertexA(Z));
        glNormal3d(_normalB(X), _normalB(Y), _normalB(Z));
        glVertex3d(_vertexB(X), _vertexB(Y), _vertexB(Z));
        glNormal3d(_normalC(X), _normalC(Y), _normalC(Z));
        glVertex3d(_vertexC(X), _vertexC(Y), _vertexC(Z));
    }
    else {
        Vectors n(normal(Vectors()));
        glNormal3d(n(X), n(Y), n(Z));
        glVertex3d(_vertexA(X), _vertexA(Y), _vertexA(Z));
        glVertex3d(_vertexB(X), _vertexB(Y), _vertexB(Z));
        glVertex3d(_vertexC(X), _vertexC(Y), _vertexC(Z));
    }
    glEnd();
    glPopMatrix();
}

//------------------------------------------------------------------------------
// normal to triangle
Vectors Triangle::normal(const Vectors &intersect) const {
    Vectors ab(_vertexB - _vertexA);
    Vectors ac(_vertexC - _vertexA);
    Vectors direction(ab.cross(ac));
    if (_smooth) {
        double denominator = direction.cross(ab).dot(ac);
        double reciprocal = (fabs(denominator) < EPSILON) ? 1.0 : 1.0 / denominator;
        Vectors pa(_vertexA - intersect);
        double beta = -pa.cross(ac).dot(direction) * reciprocal;
        double gamma = pa.cross(ab).dot(direction) * reciprocal;
        double alpha = 1.0 - beta - gamma;
        return alpha * _normalA + beta * _normalB + gamma * _normalC;
    }
    else {
        return direction;
    }
}

//------------------------------------------------------------------------------

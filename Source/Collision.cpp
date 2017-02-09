//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Collision.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Collision.h"
#include "Maze.h"
#include "Vectors.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// move
void Collision::move() {
    // clip
    clip(_start);
    double x = _start.x();
    double z = _start.z();
    int h = (int)floor(x);
    int v = (int)floor(z);
    clip(_target);
    double targetX = _target.x();
    double targetZ = _target.z();
    int targetH = (int)floor(targetX);
    int targetV = (int)floor(targetZ);

    // collision detect
    _maze->threshold(_threshold);
    _position = _target;
    _detect = false;
    // centre left
    if ((targetH < h) && (targetV == v)) {
        if (_maze->verticals()[v][h]()) {
            left(h);
        }
    }
    // top centre
    else if ((targetH == h) && (targetV < v)) {
        if (_maze->horizontals()[v][h]()) {
            top(v);
        }
    }
    // centre right
    else if ((targetH > h) && (targetV == v)) {
        if (_maze->verticals()[v][h + 1]()) {
            right(h);
        }
    }
    // bottom centre
    else if ((targetH == h) && (targetV > v)) {
        if (_maze->horizontals()[v + 1][h]()) {
            bottom(v);
        }
    }
    // top left
    else if ((targetH < h) && (targetV < v)) {
        if (((double)v - z) * (targetX - x) - ((double)h - x) * (targetZ - z) >= 0.0) {
            if (_maze->verticals()[v][h]()) {
                left(h);
                if (_maze->horizontals()[v][h]()) {
                    top(v);
                }
            }
            else if (_maze->horizontals()[v][h - 1]()) {
                top(v);
            }
        }
        else {
            if (_maze->horizontals()[v][h]()) {
                top(v);
                if (_maze->verticals()[v][h]()) {
                    left(h);
                }
            }
            else if (_maze->verticals()[v - 1][h]()) {
                left(h);
            }
        }
    }
    // top right
    else if ((targetH > h) && (targetV < v)) {
        if (((double)v - z) * (targetX - x) - ((double)(h + 1) - x) * (targetZ - z) >= 0.0) {
            if (_maze->horizontals()[v][h]()) {
                top(v);
                if (_maze->verticals()[v][h + 1]()) {
                    right(h);
                }
            }
            else if (_maze->verticals()[v - 1][h + 1]()) {
                right(h);
            }
        }
        else {
            if (_maze->verticals()[v][h + 1]()) {
                right(h);
                if (_maze->horizontals()[v][h]()) {
                    top(v);
                }
            }
            else if (_maze->horizontals()[v][h + 1]()) {
                top(v);
            }
        }
    }
    // bottom right
    else if ((targetH > h) && (targetV > v)) {
        if (((double)(v + 1) - z) * (targetX - x) - ((double)(h + 1) - x) * (targetZ - z) >= 0.0) {
            if (_maze->verticals()[v][h + 1]()) {
                right(h);
                if (_maze->horizontals()[v + 1][h]()) {
                    bottom(v);
                }
            }
            else if (_maze->horizontals()[v + 1][h + 1]()) {
                bottom(v);
            }
        }
        else {
            if (_maze->horizontals()[v + 1][h]()) {
                bottom(v);
                if (_maze->verticals()[v][h + 1]()) {
                    right(h);
                }
            }
            else if (_maze->verticals()[v + 1][h + 1]()) {
                right(h);
            }
        }
    }
    // bottom left
    else if ((targetH < h) && (targetV > v)) {
        if (((double)(v + 1) - z) * (targetX - x) - ((double)h - x) * (targetZ - z) >= 0.0) {
            if (_maze->horizontals()[v + 1][h]()) {
                top(v);
                if (_maze->verticals()[v][h]()) {
                    left(h);
                }
            }
            else if (_maze->verticals()[v + 1][h]()) {
                left(h);
            }
        }
        else {
            if (_maze->verticals()[v][h]()) {
                left(h);
                if (_maze->horizontals()[v + 1][h]()) {
                    top(v);
                }
            }
            else if (_maze->horizontals()[v + 1][h - 1]()) {
                top(v);
            }
        }
    }

    // gap
    clip(_position);
    h = (int)floor(_position.x());
    v = (int)floor(_position.z());
    // centre left
    if (_maze->verticals()[v][h]() && (_position.x() < (double)h + _gap)) {
        _position.x((double)h + _gap);
    }
    // top centre
    if (_maze->horizontals()[v][h]() && (_position.z() < (double)v + _gap)) {
        _position.z((double)v + _gap);
    }
    // centre right
    if (_maze->verticals()[v][h + 1]() && (_position.x() > (double)(h + 1) - _gap)) {
        _position.x((double)(h + 1) - _gap);
    }
    // bottom centre
    if (_maze->horizontals()[v + 1][h]() && (_position.z() > (double)(v + 1) - _gap)) {
        _position.z((double)(v + 1) - _gap);
    }
    // top left
    if (!_maze->verticals()[v][h]() && !_maze->horizontals()[v][h]()) {
        if ((v > 0) && _maze->verticals()[v - 1][h]() || (h > 0) && _maze->horizontals()[v][h - 1]()) {
            if ((_position.x() < (double)h + _gap) && (_position.z() < (double)v + _gap)) {
                if ((_position.x() - (double)h) < (_position.z() - (double)v)) {
                    _position.z((double)v + _gap);
                }
                else {
                    _position.x((double)h + _gap);
                }
            }
        }
    }
    // top right
    if (!_maze->verticals()[v][h + 1]() && !_maze->horizontals()[v][h]()) {
        if ((v > 0) && _maze->verticals()[v - 1][h + 1]() || (h < _maze->width() - 1) && _maze->horizontals()[v][h + 1]()) {
            if ((_position.x() > (double)(h + 1) - _gap) && (_position.z() < (double)v + _gap)) {
                if (((double)(h + 1) - _position.x()) < (_position.z() - (double)v)) {
                    _position.z((double)v + _gap);
                }
                else {
                    _position.x((double)(h + 1) - _gap);
                }
            }
        }
    }
    // bottom right
    if (!_maze->verticals()[v][h + 1]() && !_maze->horizontals()[v + 1][h]()) {
        if ((v < _maze->height() - 1) && _maze->verticals()[v + 1][h + 1]() || (h < _maze->width() - 1) && _maze->horizontals()[v + 1][h + 1]()) {
            if ((_position.x() > (double)(h + 1) - _gap) && (_position.z() > (double)(v + 1) - _gap)) {
                if (((double)(h + 1) - _position.x()) < ((double)(v + 1) - _position.z())) {
                    _position.z((double)(v + 1) - _gap);
                }
                else {
                    _position.x((double)(h + 1) - _gap);
                }
            }
        }
    }
    // bottom left
    if (!_maze->verticals()[v][h]() && !_maze->horizontals()[v + 1][h]()) {
        if ((v < _maze->height() - 1) && _maze->verticals()[v + 1][h]() || (h > 0) && _maze->horizontals()[v + 1][h - 1]()) {
            if ((_position.x() < (double)h + _gap) && (_position.z() > (double)(v + 1) - _gap)) {
                if ((_position.x() - (double)h) < ((double)(v + 1) - _position.z())) {
                    _position.z((double)(v + 1) - _gap);
                }
                else {
                    _position.x((double)h + _gap);
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
// clip position
void Collision::clip(Vectors &position) {
    double x = position.x();
    double y = position.y();
    double z = position.z();
    int h = (int)floor(x);
    if (h < 0) {
        x = EPSILON;
    }
    else if (h > _maze->width() - 1) {
        x = (double)_maze->width() - EPSILON;
    }
    int v = (int)floor(z);
    if (v < 0) {
        z = EPSILON;
    }
    else if (v > _maze->height() - 1) {
        z = (double)_maze->height() - EPSILON;
    }
    position.setPosition(x, y, z);
}

//------------------------------------------------------------------------------
// clip left
void Collision::left(int h) {
    _position.x((double)h + EPSILON);
    _detect = true;
}

//------------------------------------------------------------------------------
// clip right
void Collision::right(int h) {
    _position.x((double)(h + 1) - EPSILON);
    _detect = true;
}

//------------------------------------------------------------------------------
// clip top
void Collision::top(int v) {
    _position.z((double)v + EPSILON);
    _detect = true;
}

//------------------------------------------------------------------------------
// clip bottom
void Collision::bottom(int v) {
    _position.z((double)(v + 1) - EPSILON);
    _detect = true;
}

//------------------------------------------------------------------------------

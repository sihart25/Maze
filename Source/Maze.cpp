//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Maze.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <GL/glut.h>
#pragma hdrstop
#include "Maze.h"
#include "Group.h"
#include "Reader.h"
#include "Vectors.h"
#include "Plane.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
double Maze::_threshold = 0.4;

//------------------------------------------------------------------------------
// erase maze
void Maze::erase() {
    int v;
    for (v = 0; v < _height + 1; v++) {
        delete[] _horizontals[v];
    }
    for (v = 0; v < _height; v++) {
        delete[] _verticals[v];
    }
    delete[] _horizontals;
    delete[] _verticals;
}

//------------------------------------------------------------------------------
// copy maze
void Maze::copy(const Maze &maze) {
    _filename = maze._filename;
    _width = maze._width;
    _height = maze._height;
    _wall = maze._wall;
    _floor = maze._floor;
    int h;
    int v;
    _horizontals = new Wall *[_height + 1];
    for (v = 0; v < _height + 1; v++) {
        _horizontals[v] = new Wall[_width];
    }
    _verticals = new Wall *[_height];
    for (v = 0; v < _height; v++) {
        _verticals[v] = new Wall[_width + 1];
    }
    for (v = 0; v < _height + 1; v++) {
        for (h = 0; h < _width; h++) {
            _horizontals[v][h] = maze._horizontals[v][h];
        }
    }
    for (v = 0; v < _height; v++) {
        for (h = 0; h < _width + 1; h++) {
            _verticals[v][h] = maze._verticals[v][h];
        }
    }
}

//------------------------------------------------------------------------------
// read maze with static function
bool Maze::read(istream &in, string &token, Group &group) {
    if (token == "Maze") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing maze opening brace");
        }
        in >> token;
        Maze *maze = new Maze;
        group.push_back(maze);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (maze->_material.read(in, token)) {}
            else if (token == "Filename") {
                in >> maze->_filename >> token;
            }
            else if (token == "Width") {
                in >> maze->_width >> token;
            }
            else if (token == "Height") {
                in >> maze->_height >> token;
            }
            else if (token == "Wall") {
                in >> maze->_wall >> token;
            }
            else if (token == "Floor") {
                in >> maze->_floor >> token;
            }
            else {
                throw string("Error : Invalid maze attribute = " + token);
            }
        }
        in >> token;
        try {
            ifstream in(maze->_filename.c_str());
            if (!in.good()) {
                throw string("Error : Invalid file name = " + maze->_filename);
            }
            maze->readFile(in);
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
// read maze file
void Maze::readFile(istream &in) {
    int v;
    int h;
    _horizontals = new Wall *[_height + 1];
    for (v = 0; v < _height + 1; v++) {
        _horizontals[v] = new Wall[_width];
    }
    _verticals = new Wall *[_height];
    for (v = 0; v < _height; v++) {
        _verticals[v] = new Wall[_width + 1];
    }
    for (v = 0; v < _height + 1; v++) {
        for (h = 0; h < _width; h++) {
            in >> _horizontals[v][h];
        }
        if (v < _height) {
            for (h = 0; h < _width + 1; h++) {
                in >> _verticals[v][h];
            }
        }
    }
}

//------------------------------------------------------------------------------
// render maze
void Maze::render(const Game &game) const {
    int v;
    int h;
    const bool infinite = false;
    const bool texture = true;
    Vectors normal(0.0, 0.0, 1.0);
    Vectors up(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(_centre.x(), _centre.y(), _centre.z());
    for (v = 0; v < _height + 1; v++) {
        for (h = 0; h < _width; h++) {
            if (_horizontals[v][h].present()) {
                glPushMatrix();
                glTranslated((double)h + 0.5, _horizontals[v][h].height() - 0.5, (double)v);
                game.find(_wall)->render(game);
                glPopMatrix();
            }
        }
    }
    for (v = 0; v < _height; v++) {
        for (h = 0; h < _width + 1; h++) {
            if (_verticals[v][h].present()) {
                glPushMatrix();
                glTranslated((double)h, _verticals[v][h].height() - 0.5, (double)v + 0.5);
                glRotated(90.0, 0.0, 1.0, 0.0);
                game.find(_wall)->render(game);
                glPopMatrix();
            }
        }
    }
    for (v = 0; v < _height; v++) {
        for (h = 0; h < _width; h++) {
            glPushMatrix();
            glTranslated((double)h + 0.5, 0.0, (double)v + 0.5);
            game.find(_floor)->render(game);
            glPopMatrix();
        }
    }
    glPopMatrix();
}

//------------------------------------------------------------------------------

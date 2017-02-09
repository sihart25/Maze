//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Screen.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <GL/glut.h>
#pragma hdrstop
#include "Screen.h"
#include "Group.h"
#include "Colour.h"
#include "Reader.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read screen
bool Screen::read(istream &in, string &token, Group &group) {
    if (token == "Screen") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing screen opening brace");
        }
        in >> token;
        Screen *screen = new Screen();
        group.push_back(screen);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {
            }
            else if (token == "Background") {
                in >> screen->_background >> token;
            }
            else {
                throw string("Error : Invalid screen attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render screen
void Screen::render(const Game &/*game*/) const {
    glClearColor(_background(R), _background(G), _background(B), _background(A));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//------------------------------------------------------------------------------

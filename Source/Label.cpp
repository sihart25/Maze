//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Label.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <GL/glut.h>
#pragma hdrstop
#include "Label.h"
#include "Node.h"
#include "Group.h"
#include "Reader.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read label
void Label::read(istream &in, string &token, Game &game) {
    string key;
    Label *label;
    while (!in.eof()) {
        if (Reader::comment(in, token)) {
        }
        else {
            key = token;
            in >> token;
            if (token != OPENING_BRACE) {
                throw string("Error : Missing label opening brace");
            }
            in >> token;
            label = new Label();
            while (token != CLOSING_BRACE) {
                if (token == "Number") {
                    in >> label->_number >> token;
                }
                else if (token == "DisplayList") {
                    in /*>> boolalpha*/ >> label->_displayList /*>> noboolalpha*/ >> token;
                }
                else if (Node::read(in, token, *label)) {
                }
                else {
                    throw string("Error : Invalid label attribute = " + token);
                }
            }
            in >> token;
            game.insert(key, label);
            if (label->_displayList) {
                label->_list = glGenLists(1);
                glNewList(label->_list, GL_COMPILE);
                for (vector<Node *>::const_iterator node = label->_nodes.begin(); node != label->_nodes.end(); ++node) {
                    (*node)->render(game);
                }
                glEndList();
            }
        }
    }
}

//------------------------------------------------------------------------------
// render label
void Label::render(const Game &game) const {
    if (_displayList) {
        glCallList(_list);
    }
    else {
        for (vector<Node *>::const_iterator node = _nodes.begin(); node != _nodes.end(); ++node) {
            (*node)->render(game);
        }
    }
}

//------------------------------------------------------------------------------

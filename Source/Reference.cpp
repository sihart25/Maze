//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Reference.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Reference.h"
#include "Group.h"
#include "Reader.h"
#include "Label.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read reference
bool Reference::read(istream &in, string &token, Group &group) {
    if (token == "Reference") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing reference opening brace");
        }
        in >> token;
        Reference *reference = new Reference();
        group.push_back(reference);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {
            }
            else if (token == "Label") {
                in >> reference->_label >> token;
            }
            else {
                throw string("Error : Invalid reference attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render reference
void Reference::render(const Game &game) const {
    game.find(_label)->render(game);
}

//------------------------------------------------------------------------------

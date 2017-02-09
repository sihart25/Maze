//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Scene.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Scene_h
#define Scene_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Colour.h"
#include "Vectors.h"
#include "Screen.h"
#include "Group.h"
#include "Label.h"
#include "Camera.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Scene {

    public:

        void read(const string &filename, Game &game);
        void render(Game &game, const string &key);

    private:

        Group _group;

    };

} // ComputerGraphics

#endif // Scene_h

//------------------------------------------------------------------------------

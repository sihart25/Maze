//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Scene.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Scene.h"
#include "Reader.h"
#include "Group.h"
#include "Light.h"
#include "Constants.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read scene
void Scene::read(const string &filename, Game &game) {
    Reader::read(filename, game);
}

//------------------------------------------------------------------------------
// render scene
void Scene::render(Game &game, const string &key) {
    glEnable(GL_LIGHTING);
    for (int count = 0; count < GL_LIGHTS; ++count) {
        glDisable(GL_LIGHT[count]);
    }
    Light::count() = 0;
    game.key(key);
    game.find(key)->render(game);
}

//------------------------------------------------------------------------------

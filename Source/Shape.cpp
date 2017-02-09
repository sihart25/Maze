//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Shape.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Shape.h"
#include "Group.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Disc.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Maze.h"
#include "Polyhedron.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read shape
bool Shape::read(istream &in, string &token, Group &group) {
    if (Sphere::read(in, token, group)) {
        return true;
    }
    else if (Cylinder::read(in, token, group)) {
        return true;
    }
    else if (Plane::read(in, token, group)) {
        return true;
    }
    else if (Disc::read(in, token, group)) {
        return true;
    }
    else if (Triangle::read(in, token, group)) {
        return true;
    }
    else if (Mesh::read(in, token, group)) {
        return true;
    }
    else if (Maze::read(in, token, group)) {
        return true;
    }
    else if (Polyhedron::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------

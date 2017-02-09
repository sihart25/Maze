//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Collision.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Collision_h
#define Collision_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Vectors.h"
#include "Maze.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Collision {

    public:

        Collision() : _maze(0), _gap(0.25), _threshold(0.4), _start(0.0, 0.0, 0.0, 1.0), _target(0.0, 0.0, 0.0, 1.0), _position(0.0, 0.0, 0.0, 1.0), _detect(false) {}
        void maze(Maze *maze) { _maze = maze; }
        void gap(double gap) { _gap = gap; }
        void threshold(double threshold) { _threshold = threshold; }
        void start(Vectors start) { _start = start; }
        void target(Vectors target) { _target = target; }
        const Vectors &start() const { return _start; }
        const Vectors &target() const { return _target; }
        const Vectors &position() const { return _position; }
        bool detect() const { return _detect; }
        void move();

    private:

        void clip(Vectors &position);
        void left(int h);
        void right(int h);
        void top(int v);
        void bottom(int v);

        Maze *_maze;
        double _gap;
        double _threshold;
        Vectors _start;
        Vectors _target;
        Vectors _position;
        bool _detect;

    };


} // ComputerGraphics

#endif // Collision_h

//------------------------------------------------------------------------------

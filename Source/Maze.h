//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Maze.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Maze_h
#define Maze_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Shape.h"
#include "Group.h"
#include "Vectors.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const double HEIGHT_RATE = 0.04;
    const int HEIGHT_ODDS = 200;

    //------------------------------------------------------------------------------
    // class definition

    class Maze : public Shape {

        //------------------------------------------------------------------------------
        // nested class definition

        class Wall;
        friend Wall;
        class Wall {

        public:

            Wall() : _present(false), _open(false), _height(0.0) {}
            friend istream &operator>>(istream &in, Wall &wall) {
                wall.read(in);
                return in;
            }
            bool operator()() const { return _present && (_height >= _threshold); }
            void open() {
                if ((rand() % HEIGHT_ODDS) == 0) {
                    _open = true;
                }
            }
            void update() {
                if (_present) {
                    if (_open) {
                        _height -= HEIGHT_RATE;
                        if (_height < 0.0) {
                            _height = 0.0;
                            _open = false;
                        }
                    }
                    else if (_height < 1.0) {
                        _height += HEIGHT_RATE;
                        if (_height > 1.0) {
                            _height = 1.0;
                        }
                    }
                }
            }
            bool present() { return _present; }
            double height() { return _height; }

        private:

            void read(istream &in) {
                in >> _present;
                if (_present) {
                    _present = true;
                    _open = false;
                    _height = 1.0;
                }
                else {
                    _present = false;
                    _open = false;
                    _height = 0.0;
                }
            }

            bool _present;
            bool _open;
            double _height;

        };

    //------------------------------------------------------------------------------
    // class definition

    public:

        Maze() : _width(0), _height(0), _horizontals(0), _verticals(0) {}
        Maze(const Maze &maze) : Shape(maze) {
            copy(maze);
        }
        Maze &operator=(const Maze &maze) {
            if (this != &maze) {
                Shape::operator=(maze);
                erase();
                copy(maze);
            }
            return *this;
        }
        ~Maze() {
            erase();
        }
        virtual Node *clone() const { return new Maze(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;
        int width() { return _width; }
        int height() { return _height; }
        Wall **horizontals() { return _horizontals; }
        Wall **verticals() { return _verticals; }
        void threshold(double threshold) { _threshold = threshold; }
        double threshold() { return _threshold; }
        void open() {
            int v;
            int h;
            for (v = 1; v < _height; v++) {
                for (h = 0; h < _width; h++) {
                    _horizontals[v][h].open();
                }
            }
            for (v = 0; v < _height; v++) {
                for (h = 1; h < _width; h++) {
                    _verticals[v][h].open();
                }
            }
        }
        void update() {
            int v;
            int h;
            for (v = 1; v < _height; v++) {
                for (h = 0; h < _width; h++) {
                    _horizontals[v][h].update();
                }
            }
            for (v = 0; v < _height; v++) {
                for (h = 1; h < _width; h++) {
                    _verticals[v][h].update();
                }
            }
        }

    private:

        void erase();
        void copy(const Maze &maze);
        void readFile(istream &in);
        virtual void write(ostream &out) const { cout << "Maze" << endl; Shape::write(out); }

        string _filename;
        int _width;
        int _height;
        Wall **_horizontals;
        Wall **_verticals;
        string _wall;
        string _floor;
        static double _threshold;

    };

} // ComputerGraphics

#endif // Maze_h

//------------------------------------------------------------------------------

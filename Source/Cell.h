//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Cell.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Cell_h
#define Cell_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Vectors.h"
#include "Node.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Cell {

    public:

        Cell() : _label(""), _node(0) {
        }
        Cell(const Cell &cell) {
            copy(cell);
        }
        Cell &operator=(const Cell &cell) {
            if (this != &cell) {
                erase();
                copy(cell);
            }
            return *this;
        }
        ~Cell() {
            erase();
        }
        string label() const { return _label; }
        void label(string label) { _label = label; }
        Node *node() const { return _node; }
        void node(Node *node) { _node = node; }
        const Vectors &position() const { return _position; }
        void position(const Vectors &position) { _position = position; }
        const Vectors &direction() const { return _direction; }
        void direction(const Vectors &direction) { _direction = direction; }

    private:

        void erase() {
            delete _node;
        }
        void copy(const Cell &cell) {
            _label = cell._label;
            _position = cell._position;
            _direction = cell._direction;
            if (cell._node) {
                _node = cell._node->clone();
            }
            else {
                _node = 0;
            }
        }

        string _label;
        Vectors _position;
        Vectors _direction;
        Node *_node;

    };


} // ComputerGraphics

#endif // Cell_h

//------------------------------------------------------------------------------

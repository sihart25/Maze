//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Label.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Label_h
#define Label_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <GL/glut.h>
#include "Group.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Label : public Group {

    public:

        Label() : _number(0), _displayList(false), _list(0), _copy(false) {
        }
        Label(const Label &label) : Group(label) {
            copy(label);
        }
        Label &operator=(const Label &label) {
            if (this != &label) {
                Group::operator=(label);
                erase();
                copy(label);
            }
            return *this;
        }
        ~Label() {
            erase();
        }
        virtual Node *clone() const { return new Label(*this); }
        static void read(istream &in, string &token, Game &game);
        virtual void render(const Game &game) const;
        int number() { return _number; }

    private:

        void erase() {
            if (_displayList && !_copy) {
                glDeleteLists(_list, 1);
            }
        }
        void copy(const Label &label) {
            _number = label._number;
            _displayList = label._displayList;
            _list = label._list;
            _copy = true;
        }
        virtual void write(ostream &out) const { cout << "Label"; }

        int _number;
        bool _displayList;
        GLuint _list;
        bool _copy;

    };

} // ComputerGraphics

#endif // Label_h

//------------------------------------------------------------------------------

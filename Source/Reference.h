//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Reference.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Reference_h
#define Reference_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Node.h"
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

    class Reference : public Node {

    public:

        Reference(const string &label = "") : _label(label) {}
        virtual Node *clone() const { return new Reference(*this); }
        static bool read(istream &in, string &token, Group &group);
        void render(const Game &game) const;

    private:

        virtual void write(ostream &out) const { cout << "Reference" << endl; }
        string _label;

    };

} // ComputerGraphics

#endif // Reference_h

//------------------------------------------------------------------------------

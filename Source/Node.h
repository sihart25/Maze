//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Node.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Node_h
#define Node_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Group;
    class Game;

    //------------------------------------------------------------------------------
    // class definition

    class Node {

    public:

        virtual ~Node() {}
        virtual Node *clone() const = 0;
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const = 0;
        virtual void update() {}
        friend ostream &operator<<(ostream &out, const Node &node) {
            node.write(out);
            return out;
        }

    protected:

        virtual void write(ostream &out) const { cout << "Node" << endl; }

    };

} // ComputerGraphics

#endif // Node_h

//------------------------------------------------------------------------------

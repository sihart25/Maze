//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Group.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Group_h
#define Group_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Light;
    class Shape;

    //------------------------------------------------------------------------------
    // class definition

    class Group : public Node {

    public:

        Group() {
        }
        Group(const Group &group) {
            copy(group);
        }
        Group &operator=(const Group &group) {
            if (this != &group) {
                erase();
                copy(group);
            }
            return *this;
        }
        virtual ~Group() {
            erase();
        }
        virtual Node *clone() const { return new Group(*this); }
        void clear() { erase(); }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;
        virtual void update();
        void push_back(Node *node) { _nodes.push_back(node); }
        const vector<Node *> &nodes() const { return _nodes; }

    private:

        void erase();
        void copy(const Group &group);
        virtual void write(ostream &out) const { cout << "Group"; }

    protected:

        vector<Node *> _nodes;

    };

} // ComputerGraphics

#endif // Group_h

//------------------------------------------------------------------------------

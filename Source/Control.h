//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Control.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Control_h
#define Control_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <ctime>
#include "Game.h"
#include "Scene.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Control {

    public:

        enum View {
            AERIAL,
            PLAYER,
            AERIAL_WITH_PLAYER,
            PLAYER_WITH_AERIAL,
            STEREO
        };

        Control() : _wireframe(false), _motionX(0), _motionY(0), _count(0), _rate(0.0), _view(AERIAL) {
            _then = clock();
        }
        ~Control() { cout << "Control node destructed" << endl; }
        void initialize(int *argc, char **argv);
        void menu() const;
        void display();
        void reshape(int width, int height);
        void keyboard(unsigned char key, int x, int y);
        void special(int key, int x, int y);
        void mouse(int button, int state, int x, int y);
        void motion(int x, int y);
        void idle();

    private:

        void start();

        Game _game;
        Scene _scene;
        string _filename;
        bool _wireframe;
        int _motionX;
        int _motionY;
        int _count;
        clock_t _then;
        double _rate;
        View _view;

    };

} // ComputerGraphics

#endif // Control_h

//------------------------------------------------------------------------------

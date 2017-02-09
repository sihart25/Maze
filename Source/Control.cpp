//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Control.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#ifdef WIN32
#include <sstream>
#endif
#include <iomanip>
#include <ctime>
#include <GL/glut.h>
#pragma hdrstop
#include "Control.h"
#include "Scene.h"
#include "Sound.h"
#include "Reference.h"
#include "Transform.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// initialize
void Control::initialize(int *argc, char **argv) {
    if (*argc != 2) {
        _filename = string("../Data/Game.txt");
    }
    else {
        _filename = argv[1];
    }

    Sound::init(argc, argv);
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);
    GLfloat ambient[] = {0.0, 0.0, 0.0, 0.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    start();
}

//------------------------------------------------------------------------------
// menu
void Control::menu() const {
    cout << "Press <escape>               to exit program" << endl;
    cout << "Press <f1>                   to select aerial view" << endl;
    cout << "Press <f2>                   to select player view" << endl;
    cout << "Press <f3>                   to select aerial view with inset player view" << endl;
    cout << "Press <f4>                   to select player view with inset aerial view" << endl;
    cout << "Press <f5>                   to select stereo view" << endl;
    cout << "Press <f6>                   to toggle between solid and wire frame view" << endl;
    cout << "Press <f9>                   to play Doh sound" << endl;
    cout << "Press <f10>                  to play Ahhhhh sound" << endl;
    cout << "Press <f11>                  to play Woohoo sound" << endl;
    cout << "Press <f12>                  to play Hallelujah" << endl;
    cout << "Press <space>                to restart game" << endl;
    cout << "Press <left,right>           to rotate" << endl;
    cout << "Press <down,up>              to move" << endl;
    cout << "Press mouse button and move  to rotate and move" << endl;
}

//------------------------------------------------------------------------------
// start
void Control::start() {
    _game = Game();
    _scene.read(_filename, _game);
    _game.start();
}

//------------------------------------------------------------------------------
// display
void Control::display() {
    _game.play();
    #ifdef WIN32
    ostringstream oss;
    oss << setiosflags(ios::fixed) << setprecision(2);
    oss << "OpenGL Maze ... Frame Rate " << _rate << " fps ... Top Score " << _game.topScore() << " ... Score " << _game.score() << (_game.over() ? " ... Game Over" : "");
    glutSetWindowTitle(oss.str().c_str());
    #else
    glutSetWindowTitle("OpenGL Maze");
    #endif
    glPolygonMode(GL_FRONT_AND_BACK, !_wireframe ? GL_FILL : GL_LINE);
    _scene.render(_game, "Screen");
    switch (_view) {
        case PLAYER: {
            glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            _scene.render(_game, "PlayerView");
            break;
        }
        case AERIAL: {
            glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            _scene.render(_game, "AerialView");
            break;
        }
        case PLAYER_WITH_AERIAL: {
            glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            _scene.render(_game, "PlayerView");
            glClear(GL_DEPTH_BUFFER_BIT);
            glViewport(glutGet(GLUT_WINDOW_WIDTH) * 5 / 8, glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
            _scene.render(_game, "AerialView");
            break;
        }
        case AERIAL_WITH_PLAYER: {
            glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            _scene.render(_game, "AerialView");
            glClear(GL_DEPTH_BUFFER_BIT);
            glViewport(glutGet(GLUT_WINDOW_WIDTH) * 3 / 4, glutGet(GLUT_WINDOW_HEIGHT) * 3 / 4, glutGet(GLUT_WINDOW_WIDTH) / 4, glutGet(GLUT_WINDOW_HEIGHT) / 4);
            _scene.render(_game, "PlayerView");
            break;
        }
        case STEREO: {
            const double border = 0.01;
            glViewport((int)(border * glutGet(GLUT_WINDOW_WIDTH) / 2), (int)(border * glutGet(GLUT_WINDOW_HEIGHT)), (int)((1.0 - 1.5 * border) * glutGet(GLUT_WINDOW_WIDTH) / 2), (int)((1.0 - 2.0 * border) * glutGet(GLUT_WINDOW_HEIGHT)));
            _scene.render(_game, "LeftView");
            glViewport((int)((1.0 + border) * glutGet(GLUT_WINDOW_WIDTH) / 2), (int)(border * glutGet(GLUT_WINDOW_HEIGHT)), (int)((1.0 - 1.5 * border) * glutGet(GLUT_WINDOW_WIDTH) / 2), (int)((1.0 - 2.0 * border) * glutGet(GLUT_WINDOW_HEIGHT)));
            _scene.render(_game, "RightView");
            break;
        }
    }
    glutSwapBuffers();
    _count++;
}

//------------------------------------------------------------------------------
// reshape
void Control::reshape(int width, int height) {
}

//------------------------------------------------------------------------------
// keyboard
void Control::keyboard(unsigned char key, int /*x*/, int /*y*/) {
    switch (key) {
        case ' ': {
            start();
            break;
        }
        case 0x1B: {
            glutDestroyWindow(glutGetWindow());
            delete this;
            Sound::close();
            exit(0);
        }
        default: {
            return;
        }
    }
}

//------------------------------------------------------------------------------
// special
void Control::special(int key, int /*x*/, int /*y*/) {
    const double ANGLE_INCREMENT = 10.0;
    const double POSITION_INCREMENT = 0.2;
    switch (key) {
        case GLUT_KEY_F1: {
            _view = AERIAL;
            break;
        }
        case GLUT_KEY_F2: {
            _view = PLAYER;
            break;
        }
        case GLUT_KEY_F3: {
            _view = AERIAL_WITH_PLAYER;
            break;
        }
        case GLUT_KEY_F4: {
            _view = PLAYER_WITH_AERIAL;
            break;
        }
        case GLUT_KEY_F5: {
            _view = STEREO;
            break;
        }
        case GLUT_KEY_F6: {
            _wireframe = !_wireframe;
            break;
        }
        case GLUT_KEY_F9: {
            _game.find("Doh")->render(_game);
            break;
        }
        case GLUT_KEY_F10: {
            _game.find("Ahhhhh")->render(_game);
            break;
        }
        case GLUT_KEY_F11: {
            _game.find("Woohoo")->render(_game);
            break;
        }
        case GLUT_KEY_F12: {
            _game.find("Hallelujah")->render(_game);
            break;
        }
        default: {
            switch (key) {
                case GLUT_KEY_LEFT: {
                    _game.move(ANGLE_INCREMENT, 0.0);
                    break;
                }
                case GLUT_KEY_RIGHT: {
                    _game.move(-ANGLE_INCREMENT, 0.0);
                    break;
                }
                case GLUT_KEY_DOWN: {
                    _game.move(0.0, -POSITION_INCREMENT);
                    break;
                }
                case GLUT_KEY_UP: {
                    _game.move(0.0, POSITION_INCREMENT);
                    break;
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
// mouse
void Control::mouse(int button, int state, int x, int y) {
    _motionX = x;
    _motionY = y;
}

//------------------------------------------------------------------------------
// motion
void Control::motion(int x, int y) {
    const double ANGLE_INCREMENT = 1.0;
    const double POSITION_INCREMENT = 0.02;
    _game.move(-(x - _motionX) * ANGLE_INCREMENT, (_motionY - y) * POSITION_INCREMENT);
    _motionX = x;
    _motionY = y;
}

//------------------------------------------------------------------------------
// idle
void Control::idle() {
    glutPostRedisplay();
    const double INTERVAL = 1.0;
    double interval;
    clock_t now;
    now = clock();
    if ((interval = double(now - _then) / CLOCKS_PER_SEC) > INTERVAL) {
        _rate = (double)_count / interval;
        _then = now;
        _count = 0;
    }
}

//------------------------------------------------------------------------------

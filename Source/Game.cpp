//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Game.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <ctime>
#pragma hdrstop
#include "Game.h"
#include "Label.h"
#include "Transform.h"
#include "Reference.h"
#include "Camera.h"
#include "Vectors.h"
#include "Constants.h"
#include "Maze.h"
#include "Group.h"
#include "Cell.h"
#include "Collision.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
int Game::_topScore = 0;

//------------------------------------------------------------------------------
// erase game
void Game::erase() {
    for (map<string, Label *>::iterator label = _labels.begin(); label != _labels.end(); ++label) {
        delete label->second;
    }
    _labels.clear();
    for (int i = 0; i < _height; i++) {
        delete[] _cells[i];
    }
    delete[] _cells;
    if (_score > _topScore) {
        _topScore = _score;
    }
}

//------------------------------------------------------------------------------
// copy game
void Game::copy(const Game &game) {
    _width = game._width;
    _height = game._height;
    _position = game._position;
    _direction = game._direction;
    _score = game._score;
    _over = game._over;
    for (map<string, Label *>::const_iterator label = game._labels.begin(); label != game._labels.end(); ++label) {
        insert(label->first, label->second);
    }
    _cells = new Cell *[_height];
    for (int i = 0; i < _height; i++) {
        _cells[i] = new Cell[_width];
    }
    for (int v = 0; v < _height; v++) {
        for (int h = 0; h < _width; h++) {
            _cells[v][h] = game._cells[v][h];
        }
    }
}

//------------------------------------------------------------------------------
// resize game
void Game::resize(int width, int height) {
    int i;
    for (i = 0; i < _height; i++) {
        delete[] _cells[i];
    }
    delete[] _cells;
    _width = width;
    _height = height;
    _cells = new Cell *[_height];
    for (i = 0; i < _height; i++) {
        _cells[i] = new Cell[_width];
    }
}

//------------------------------------------------------------------------------
// start game
void Game::start() {
    srand((unsigned int)time(NULL));
    Maze *maze = (Maze *)(find("Maze")->nodes()[0]);
    resize(maze->width(), maze->height());
    fill("Player");
    fill("Grub");
    fill("Coin");
    fill("SmallRhombicOsidodecahedron");
    fill("TruncatedIcosahedron");
    for (int v = 0; v < _height; v++) {
        for (int h = 0; h < _width; h++) {
            if (_cells[v][h].label() == "Player") {
                _position.setPosition((double)h + 0.5, 0.5, (double)v + 0.5);
                double angle = (double)(rand() % 360) / 180.0 * PI;
                _direction.setDirection(cos(angle), 0.0, sin(angle));
                move(0.0, 0.0);
            }
        }
    }
    view("AerialView", "AerialCamera", "Scene");
    view("PlayerView", "PlayerCamera", "Scene");
    view("LeftView", "PlayerCamera", "Scene");
    view("RightView", "PlayerCamera", "Scene");
}

//------------------------------------------------------------------------------
// fill game
void Game::fill(const string &label) {
    int v;
    int h;
    for (int i = 0; i < find(label)->number(); i++) {
        while (_cells[v = rand() % _height][h = rand() % _width].label() != "" ) {
        }
        _cells[v][h].label(label);
        _cells[v][h].node(find(label)->clone());
        _cells[v][h].position(Vectors((double)h + 0.5, 0.5, (double)v + 0.5, 1.0));
        double angle = (double)(rand() % 360) / 180.0 * PI;
        _cells[v][h].direction(Vectors(cos(angle), 0.0, sin(angle), 0.0));
    }
}

//------------------------------------------------------------------------------
// view game
void Game::view(const string &view, const string &camera, const string &scene) {
    Label *label;
    if (_labels.find(view) != _labels.end()) {
        delete _labels.find(view)->second;
        _labels.erase(view);
    }
    label = new Label();
    label->push_back(new Reference(camera));
    label->push_back(new Reference(scene));
    insert(view, label);
}

//------------------------------------------------------------------------------
// play game
void Game::play() {
    Label *label;
    Group *group;
    Transform *transform;
    int h;
    int v;

    // move grubs
    for (v = 0; v < _height; v++) {
        for (h = 0; h < _width; h++) {
            if (_cells[v][h].node()) {
                if (_cells[v][h].label() == "Grub") {
                    // rotate grub to face player
                    const double GRUB_ROTATION = 0.1;
                    const double GRUB_DISTANCE = 0.01;
                    Vectors direction = _cells[v][h].direction();
                    direction += GRUB_ROTATION * (_position - _cells[v][h].position()).normalize();
                    direction.normalize();
                    _cells[v][h].direction(direction);

                    // check grub for collisions
                    const double GRUB_GAP = 0.45;
                    const double GRUB_THRESHOLD = -0.1;
                    Collision collision;
                    collision.maze((Maze *)(find("Maze")->nodes()[0]));
                    collision.gap(GRUB_GAP);
                    collision.threshold(GRUB_THRESHOLD);
                    collision.start(_cells[v][h].position());
                    collision.target(_cells[v][h].position() + GRUB_DISTANCE * _cells[v][h].direction());
                    collision.move();
                    Vectors start = collision.start();
                    int startH = (int)floor(start.x());
                    int startV = (int)floor(start.z());
                    _cells[v][h].position(collision.position());
                    int endH = (int)floor(_cells[v][h].position().x());
                    int endV = (int)floor(_cells[v][h].position().z());

                    // move grub to new cell unless player occupies that cell
                    if (endH != startH || endV != startV) {
                        if (_cells[endV][endH].label() != "Player") {
                            if (_cells[endV][endH].label() != "") {
                                find("Ahhhhh")->render(*this);
                            }
                            _cells[endV][endH] = _cells[startV][startH];
                        }
                        else {
                            find("Ahhhhh")->render(*this);
                        }
                        _cells[startV][startH] = Cell();
                    }

                    // kill grub if player occupies orthogonally adjacent cell
                    Maze *maze = (Maze *)(find("Maze")->nodes()[0]);
                    if ((_cells[endV][endH].position() - _position).magnitude() < 1.0) {
                        if (!maze->verticals()[endV][endH]() && (_cells[endV][endH - 1].label() == "Player")
                            || !maze->horizontals()[endV][endH]() && (_cells[endV - 1][endH].label() == "Player")
                            || !maze->verticals()[endV][endH + 1]() && (_cells[endV][endH + 1].label() == "Player")
                            || !maze->horizontals()[endV + 1][endH]() && (_cells[endV + 1][endH].label() == "Player")) {
                            _cells[endV][endH] = Cell();
                            find("Ahhhhh")->render(*this);
                        }
                    }
                }
            }
        }
    }

    // move player away from closing walls
    const double PLAYER_GAP = 0.25;
    const double PLAYER_THRESHOLD = 0.4;
    Collision collision;
    collision.maze((Maze *)(find("Maze")->nodes()[0]));
    collision.gap(PLAYER_GAP);
    collision.threshold(PLAYER_THRESHOLD);
    collision.start(_position);
    collision.target(_position);
    collision.move();
    _position = collision.position();

    // update player camera
    Camera *camera = (Camera *)(find("PlayerCamera")->nodes()[0]);
    camera->position(_position);
    camera->direction(_direction);

    // create scene
    if (_labels.find("Scene") != _labels.end()) {
        delete _labels.find("Scene")->second;
        _labels.erase("Scene");
    }
    label = new Label();
    label->push_back(new Reference("Lights"));
    label->push_back(new Reference("Maze"));
    for (v = 0; v < _height; v++) {
        for (h = 0; h < _width; h++) {
            if (_cells[v][h].node()) {
                group = new Group();
                label->push_back(group);
                transform = new Transform();
                if (_cells[v][h].label() == "Player") {
                    transform->translate(_position);
                    transform->axis(Vectors(0.0, 1.0, 0.0));
                    transform->angle(atan2(_direction.x(), _direction.z()) / PI * 180.0);
                }
                else {
                    transform->translate(_cells[v][h].position());
                    transform->axis(Vectors(0.0, 1.0, 0.0));
                    transform->angle(atan2(_cells[v][h].direction().x(), _cells[v][h].direction().z()) / PI * 180.0);
                }
                group->push_back(transform);
                group->push_back(_cells[v][h].node()->clone());
            }
        }
    }
    insert("Scene", label);

    // update maze for opening and closing walls
    Maze *maze = (Maze *)(find("Maze")->nodes()[0]);
    maze->open();
    maze->update();

    // update scene for spins
    for (v = 0; v < _height; v++) {
        for (h = 0; h < _width; h++) {
            if (_cells[v][h].node()) {
                _cells[v][h].node()->update();
            }
        }
    }

    // game over
    if (!_over) {
        _over = true;
        for (v = 0; v < _height; v++) {
            for (h = 0; h < _width; h++) {
                if (_cells[v][h].label() != "" && _cells[v][h].label() != "Player") {
                    _over = false;
                }
            }
        }
        if (_over) {
            find("Hallelujah")->render(*this);
        }
    }
}

//------------------------------------------------------------------------------
// move player
void Game::move(double rotation, double distance) {
    // rotate and move player
    distance = (distance < -1.0 + EPSILON) ? -1.0 + EPSILON : ((distance > 1.0 - EPSILON) ? 1.0 - EPSILON : distance);
    double c = cos(rotation / 180.0 * PI);
    double s = sin(rotation / 180.0 * PI);
    _direction = Vectors(_direction.x() * c + _direction.z() * s, _direction.y(), _direction.z() * c - _direction.x() * s);
    _direction.normalize();

    // check player for collisions
    const double PLAYER_GAP = 0.25;
    const double PLAYER_THRESHOLD = 0.4;
    Collision collision;
    collision.maze((Maze *)(find("Maze")->nodes()[0]));
    collision.gap(PLAYER_GAP);
    collision.threshold(PLAYER_THRESHOLD);
    collision.start(_position);
    collision.target(_position + distance * _direction);
    collision.move();
    Vectors start = collision.start();
    int startH = (int)floor(start.x());
    int startV = (int)floor(start.z());
    _position = collision.position();
    int endH = (int)floor(_position.x());
    int endV = (int)floor(_position.z());

    // player collides with wall
    if (collision.detect()) {
        find("Doh")->render(*this);
    }

    // player kills grub
    if (_cells[endV][endH].label() == "Grub") {
        find("Ahhhhh")->render(*this);
        _score++;
    }
    // player collects treasure
    else if ((_cells[endV][endH].label() == "Coin")
        || (_cells[endV][endH].label() == "SmallRhombicOsidodecahedron")
        || (_cells[endV][endH].label() == "TruncatedIcosahedron")) {
        find("Woohoo")->render(*this);
        _score++;
    }

    // move player
    if (endH != startH || endV != startV) {
        _cells[endV][endH] = _cells[startV][startH];
        _cells[startV][startH] = Cell();
    }
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Game.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Game_h
#define Game_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <map>
#include "Vectors.h"
#include "Node.h"
#include "Cell.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Label;

    //------------------------------------------------------------------------------
    // class definition

    class Game {

    public:

        Game() : _width(10), _height(10), _score(0), _over(false), _key("") {
            _cells = new Cell *[_height];
            for (int i = 0; i < _height; i++) {
                _cells[i] = new Cell[_width];
            }
        }
        Game(const Game &game) {
            copy(game);
        }
        Game &operator=(const Game &game) {
            if (this != &game) {
                erase();
                copy(game);
            }
            return *this;
        }
        ~Game() {
            erase();
        }
        void start();
        void fill(const string &label);
        void view(const string &view, const string &camera, const string &scene);
        void play();
        void move(double rotation, double distance);
        void insert(const string &key, Label *label) {
            _labels.insert(make_pair<string, Label *>(key, label));
        }
        Label *find(const string &key) const {
            return (Label *)(_labels.find(key)->second);
        }
        int score() {
            return _score;
        }
        bool over() {
            return _over;
        }
        static int topScore() {
            return _topScore;
        }
        const string &key() const { return _key; }
        void key(const string &key) { _key = key; }

    private:

        void erase();
        void copy(const Game &game);
        void resize(int width, int height);
        int _width;
        int _height;
        Cell **_cells;
        Vectors _position;
        Vectors _direction;
        map<string, Label *> _labels;
        int _score;
        bool _over;
        static int _topScore;
        string _key;

    };

} // ComputerGraphics

#endif // Game_h

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Sound.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Sound_h
#define Sound_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <map>
#ifdef _OPENAL
#include <AL/alut.h>
#endif
#include "Node.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const int VOICES = 10;

    //------------------------------------------------------------------------------
    // class definition

    class Sound : public Node {

    public:

        Sound() {
            #ifdef _OPENAL
            _voice = 0;
            _buffer = 0;
            for (int voice = 0; voice < VOICES; voice++) {
                _sources[voice] = 0;
            }
            #endif
        }
        ~Sound() {
            #ifdef _OPENAL
            alDeleteSources(VOICES, _sources);
            alDeleteBuffers(1, &_buffer);
            #endif
        }
        virtual Node *clone() const { return 0; }
        static void init(int *argc, char **argv);
        static void close();
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &/*game*/) const {
            #ifdef _OPENAL
            alSourcePlay(_sources[_voice]);
            _voice = (_voice + 1) % VOICES;
            #endif
        }

    private:

        Sound(const Sound &sound);
        Sound &operator=(const Sound &sound);
        virtual void write(ostream &out) const { cout << "Sound" << endl; }

        string _filename;
        #ifdef _OPENAL
        mutable int _voice;
        ALuint _buffer;
        ALuint _sources[VOICES];
        #endif

    };

} // ComputerGraphics

#endif // Sound_h

//------------------------------------------------------------------------------

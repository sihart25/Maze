//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Sound.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <map>
#ifdef _OPENAL
#include <AL/alut.h>
#endif
#pragma hdrstop
#include "Sound.h"
#include "Group.h"
#include "Reader.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// init sound
void Sound::init(int *argc, char **argv) {
    #ifdef _OPENAL
	alutInit(argc, argv);
    ALfloat listenerPos[] = {0.0, 0.0, 0.0};
    ALfloat listenerVel[] = {0.0, 0.0, 0.0};
    ALfloat	listenerOri[] = {0.0, 0.0, 1.0, 0.0, 1.0, 0.0};
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
    #endif
}

//------------------------------------------------------------------------------
// close sound
void Sound::close() {
    #ifdef _OPENAL
	alutExit();
    #endif
}

//------------------------------------------------------------------------------
// read sound with static method
bool Sound::read(istream &in, string &token, Group &group) {
    if (token == "Sound") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing sound opening brace");
        }
        in >> token;
        Sound *sound = new Sound;
        group.push_back(sound);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            if (token == "Filename") {
                in >> sound->_filename >> token;
            }
            else {
                throw string("Error : Invalid sound attribute = " + token);
            }
        }
        in >> token;
        #ifdef _OPENAL
        int voice;
        alGenBuffers(1, &sound->_buffer);
        if (!alIsBuffer(sound->_buffer)) {
		    throw string("Error : Failed sound buffer creation");
	    }
	    ALenum format;
	    ALvoid *data;
	    ALsizei size;
        ALsizei freq;
        #ifdef WIN32
	    alutLoadWAVFile(const_cast<ALbyte *>(sound->_filename.c_str()), &format, &data, &size, &freq);
	    alBufferData(sound->_buffer, format, data, size, freq);
	    alutUnloadWAV(format, data, size, freq);
        #else
        ALsizei bits
	    alutLoadWAV(const_cast<ALbyte *>(sound->_filename.c_str()), &data, &format, &size, &bits, &freq);
	    alBufferData(sound->_buffer, format, data, size, freq);
	    free(data);
        #endif
        alGenSources(VOICES, sound->_sources);
        for (voice = 0; voice < VOICES; voice++) {
            if (!alIsSource(sound->_sources[voice])) {
    		    throw string("Error : Failed sound source creation");
	        }
            ALfloat sourcePos[] = {0.0, 0.0, 1.0};
            ALfloat sourceVel[] = {0.0, 0.0, 1.0};
	        alSourcef(sound->_sources[voice], AL_PITCH, 1.0f);
	        alSourcef(sound->_sources[voice], AL_GAIN, 1.0f);
	        alSourcefv(sound->_sources[voice], AL_POSITION, sourcePos);
	        alSourcefv(sound->_sources[voice], AL_VELOCITY, sourceVel);
	        alSourcei(sound->_sources[voice], AL_BUFFER, sound->_buffer);
	        alSourcei(sound->_sources[voice], AL_LOOPING, AL_FALSE);
        }
        #endif
        return true;
    }
    else {
        return false;
    }
}

//------------------------------------------------------------------------------

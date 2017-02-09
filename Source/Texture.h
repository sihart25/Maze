//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// Maze Assessment
// Texture.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Texture_h
#define Texture_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Node.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Texture : public Node {

    public:

        Texture() : _texture(0), _mipmap(false) {
        }
        ~Texture() {
            glDeleteTextures(1, &_texture);
        }
        virtual Node *clone() const { return 0; }
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &/*game*/) const {
            glBindTexture(GL_TEXTURE_2D, _texture);
        }

    private:

        Texture(const Texture &texture);
        Texture &operator=(const Texture &texture);
        virtual void write(ostream &out) const { cout << "Texture" << endl; }

        string _filename;
        bool _mipmap;
        GLuint _texture;

    };

} // ComputerGraphics

#endif // Texture_h

//------------------------------------------------------------------------------

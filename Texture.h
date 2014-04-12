#ifndef TEXTURE_H
#define TEXTURE_H
// GLEW for all platform
#include <GL/glew.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "Error.h"
class Texture
{
    public:
        Texture(const std::string &filename = "");
        // for FBO
        Texture(int largeur, int hauteur, GLenum format, GLenum formatInterne, bool textureVide);
        Texture(const Texture &toCopy);
        Texture& operator=(const Texture &toCopy);
        bool load();
        void LoadEmptyTexture();

        GLuint getID () const;
        void    setFilename(const std::string &filename);
        virtual ~Texture();
    protected:
        GLuint                  m_id;
        std::string             m_filename;
        // for FBO
        int                     m_largeur;
        int                     m_hauteur;
        GLenum                  m_format;
        GLenum                  m_formatInterne;
        bool                    m_textureVide;
    private:
};

#endif // TEXTURE_H

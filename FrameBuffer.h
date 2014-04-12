#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

// GLEW for all platform
#include <GL/glew.h>
#include <vector>
#include "Error.h"
#include "Texture.h"
class FrameBuffer
{
    public:
        FrameBuffer();
        FrameBuffer(int largeur, int hauteur);
        void    CreerRenderBuffer(GLuint &id, GLenum formatInterne);
        bool    Load();
         ~FrameBuffer();
        GLuint  GetID()const;
        GLuint  GetColorBufferID(unsigned int index) const;

        int     GetLargeur() const;
        int     GetHauteur() const;
    protected:
        GLuint                  m_id;

        int                     m_largeur;
        int                     m_hauteur;

        std::vector <Texture>   m_colorBuffers;
        GLuint                  m_depthBufferID;
    private:
};

#endif // FRAMEBUFFER_H

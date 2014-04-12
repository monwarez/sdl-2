/*
Copyright (C) 2014 Payet thibault

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
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
        void    Load(); // peut lancer une exception de type Error -ie ne pas oublier les blocs try/catch
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

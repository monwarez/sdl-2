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
#include "Graphics.h"

CGraphics::CGraphics(GLuint width, GLuint height, bool fullscreen,const std::string &title,
                     GLuint bpp, GLuint aa, GLuint major, GLuint minor ):m_bpp(bpp),m_aa(aa)
{
    m_pWindow       =   new Window(title, width, height,fullscreen);

    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,   major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,   minor);
    // profile core
	
	if ((major >= 3 && minor >= 2) || major >= 4)
    	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	else if (3 == major)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_glContext     =   m_pWindow->CreateContext(0); // on a qu'une seule fen�tre
    GL_CHECK;

    if (m_glContext == 0)
        throw GEST_ERROR(SDL_GetError())
    try
    {

        glewExperimental    =   GL_TRUE;
        GLenum  initialisationGLEW(glewInit());

        if (initialisationGLEW != GLEW_OK)
            throw GEST_ERROR((char*)glewGetErrorString(initialisationGLEW))


    }
    catch (Error error)
    {
        error.ShowError();
        exit(-1);
    }
    std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
}
void        CGraphics::SwapWindow()
{
    m_pWindow->SwapWindow(0);
}
CGraphics::~CGraphics()
{
    SDL_GL_DeleteContext(m_glContext);
    delete m_pWindow;

}

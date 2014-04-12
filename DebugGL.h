#ifndef DEBUGGL_H_INCLUDED
#define DEBUGGL_H_INCLUDED

// GLEW for all platform
#include <GL/glew.h>

#include <string>
#include <iostream>

#define GL_CHECK Debug::glCheck(__FILE__,__LINE__)

namespace Debug
{
    bool glCheck(std::string filename, int line);

};

#endif // DEBUGGL_H_INCLUDED

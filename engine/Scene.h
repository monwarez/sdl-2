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
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "Object.h"
#include "../util/Shader.h"
#include "../util/Input.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include <vector>

template <typename T>
struct  Noeud
{
    T   val;
    Noeud*  previous;
    Noeud*  next;
};
template <typename T>
class   Arbre
{

};
class   CScene
{
    public:
        CScene(std::string shaderPath="./Shaders/");
        virtual ~CScene();
        virtual     void        Show(Uint32 elapsed, GLsizei width, GLsizei height);
        virtual     int         AttachObject(IObject *object); // pour l'instant retourne un indice
        virtual     void        AttachInput(CInput *input);
        virtual     void        SetPerspective(GLfloat fov, GLfloat width, GLfloat height, GLfloat near, GLfloat far);
    protected:
        std::vector < IObject *>    m_pObject;

        Shader*                     m_pShader;
        ShaderUniformMatrix         m_uniformMatrix;
        ShaderUniformMatrix         m_uniformMatrixFBO;
        CInput*                     m_pCInput;
        Camera*                     m_pCamera;
        FrameBuffer*                m_pFBO;
        QuadObject                  m_quad;

};

#endif // SCENE_H_INCLUDED

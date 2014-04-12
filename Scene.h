#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "Object.h"
#include "Shader.h"
#include "Input.h"
#include "Camera.h"
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
        CScene();
        virtual ~CScene();
        virtual     void        Show(Uint32 elapsed);
        virtual     int         AttachObject(IObject *object); // pour l'instant retourne un indice
        virtual     void        AttachInput(CInput *input);
    protected:
        std::vector < IObject *>    m_pObject;

        Shader*                     m_pShader;
        ShaderUniformMatrix         m_uniformMatrix;
        CInput*                     m_pCInput;
        Camera*                     m_pCamera;

};

#endif // SCENE_H_INCLUDED

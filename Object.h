#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Graphics.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "MD2Loader.h"

#include "DebugGL.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif
struct ShaderUniformMatrix
{
    glm::mat4 modelview;
    glm::mat4 projection;
    GLuint    modelviewLocation;
    GLuint    projectionLocation;
    GLuint    mvpLocation;
};
class IObject
{
    public:
        IObject();
        virtual ~IObject();
        virtual void        Show(ShaderUniformMatrix uniformMatrix, Uint32 fps) =0;
};
class CubeObject : public IObject
{
    public:
        CubeObject();
        void SetIDTexture(GLuint IDtexture);
        virtual ~CubeObject();

        virtual void        Show(ShaderUniformMatrix uniformMatrix, Uint32 fps);

    protected:
        GLuint              m_vao;
        GLuint              m_vbo;
        GLsizei             m_tailleVerticesBytes;
        GLsizei             m_tailleCoordBytes;
        GLuint              m_IDtexture;


};
class   MD2Object   :   public IObject
{
    public:
        MD2Object(CEntity *entityModel); // on disposera d'un gestionnaire de ressource
        virtual ~MD2Object();

        virtual void        Show(ShaderUniformMatrix, Uint32 fps);
        virtual void        SetAnimation(int start, int fin, bool animated);

    protected:
        CEntity*            m_entity;
        int                 m_start;
        int                 m_end;
        bool                m_animated;
};
#endif // OBJECT_H_INCLUDED

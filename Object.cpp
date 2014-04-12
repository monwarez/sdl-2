#include "Object.h"

IObject::IObject()
{

}
IObject::~IObject()
{

}
CubeObject::CubeObject()
{


    GLfloat     vertices[]  =   {   0,0,0,   0,1,0,    0,1,1,
                                    0,0,1, 1,0,0 , 1,1,0 , 0,1,0
                                    };


    GLfloat     coordTex[]  = {  0,0 , 1,0,    1,1,
                                 0,1 , 1,0, 1,1 , 1,0 };

    m_tailleCoordBytes      =   14 * sizeof(GLfloat);
    m_tailleVerticesBytes     =   21 * sizeof(GLfloat);


        glGenBuffers(1,&m_vbo);
        glGenVertexArrays(1,&m_vao);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCoordBytes, 0, GL_DYNAMIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes,vertices);
            glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCoordBytes, coordTex);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
        glBindVertexArray(0);




}
void    CubeObject::SetIDTexture(GLuint IDTexture)
{
    m_IDtexture     =   IDTexture;
}
CubeObject::~CubeObject()
{
    glDeleteBuffers(1,&m_vbo);

    glDeleteVertexArrays(1,&m_vao);
}
void        CubeObject::Show(ShaderUniformMatrix uniformMatrix, Uint32 fps)
{



    // � optimiser pour l'envoi des matrices
    glUniformMatrix4fv(uniformMatrix.modelviewLocation, 1, GL_FALSE, glm::value_ptr(uniformMatrix.modelview));
    //glUniformMatrix4fv(uniformMatrix.projectionLocation, 1, GL_FALSE, glm::value_ptr(uniformMatrix.projection));

    glm::mat4 mvp = uniformMatrix.projection * uniformMatrix.modelview;
    glUniformMatrix4fv(uniformMatrix.mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

        glBindVertexArray(m_vao);
            glBindTexture(GL_TEXTURE_2D, m_IDtexture);
                glDrawArrays(GL_TRIANGLE_FAN,0,7);

            glBindTexture(GL_TEXTURE_2D,0);
        glBindVertexArray(0);


}
MD2Object::MD2Object(CEntity *entityModel)
{
    m_entity            =   entityModel;
}
MD2Object::~MD2Object()
{

}
void    MD2Object::SetAnimation(int start, int fin, bool animated)
{
    m_start             =   start;
    m_end               =   fin;
    m_animated          =   animated;
}
void    MD2Object::Show(ShaderUniformMatrix uniformMatrix, Uint32 fps)
{
    // � optimiser pour l'envoi des matrices
    glUniformMatrix4fv(uniformMatrix.modelviewLocation, 1, GL_FALSE, glm::value_ptr(uniformMatrix.modelview));
    //glUniformMatrix4fv(uniformMatrix.projectionLocation, 1, GL_FALSE, glm::value_ptr(uniformMatrix.projection));

    glm::mat4 mvp = uniformMatrix.projection * uniformMatrix.modelview;
    glUniformMatrix4fv(uniformMatrix.mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

    m_entity->Animate(m_start,m_end,10.0/fps);
    m_entity->DrawEntity(-1, m_animated, false);
}
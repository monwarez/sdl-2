#include "Scene.h"

CScene::CScene()
{
    m_pShader   =   new Shader("Shaders/texture.vert","Shaders/texture.frag");
    m_pShader->charger();
    m_uniformMatrix.modelview   =   glm::mat4(1);
    m_uniformMatrix.projection  =   glm::perspective(70.0, 1024/768.0, 0.01,100.0);
    m_pCInput                   =   0;
    m_pCamera                   =   new Camera(glm::vec3(-1,-1,1),glm::vec3(0,0,0),glm::vec3(0,0,1));

    m_pCamera->setSpeed(0.01);

}
CScene::~CScene()
{
    delete m_pShader;
    delete m_pCamera;

}
void    CScene::Show(Uint32 elapsed)
{

    GLuint shaderID =   m_pShader->getProgramID();
    // camera
    m_pCamera->keyBoardEvent(*m_pCInput);
    m_pCamera->deplacer(*m_pCInput,elapsed);
    m_pCamera->lookAt(m_uniformMatrix.modelview);
    glUseProgram(shaderID);
    glEnable(GL_DEPTH_TEST);
        m_uniformMatrix.modelviewLocation   =   glGetUniformLocation(shaderID, "modelview");
        m_uniformMatrix.mvpLocation         =   glGetUniformLocation(shaderID,"modelviewprojection");



        for (unsigned int i=0; i < m_pObject.size(); ++i)
        {
            m_pObject[i]->Show(m_uniformMatrix, elapsed);
        }
    glUseProgram(0);


}
int    CScene::AttachObject(IObject *objet)
{
    m_pObject.push_back(objet);
    return m_pObject.size() - 1 ;
}
void    CScene::AttachInput(CInput  *input)
{
    m_pCInput   =   input;
}

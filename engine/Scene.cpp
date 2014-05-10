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
#include "Scene.h"

CScene::CScene(std::string ShaderPath)
{

    m_pShader   =   new Shader(ShaderPath + std::string("texture.vert"),ShaderPath + std::string("texture.frag"));
    m_pShader->charger();
    m_uniformMatrix.modelview   =   glm::mat4(1);
    m_uniformMatrix.projection  =   glm::perspective(70.0, 1600.0/900, 0.01,100.0);
    m_pCInput                   =   0;
    m_pCamera                   =   new Camera(glm::vec3(-1,-1,1),glm::vec3(0,0,0),glm::vec3(0,0,1));

    m_pCamera->setSpeed(0.01);
    m_pFBO                      =   new FrameBuffer(128,128);
    m_pFBO->Load();

    m_uniformMatrixFBO.projection=  glm::perspective(70.0, (double)m_pFBO->GetLargeur()/m_pFBO->GetHauteur(),1.0,100.0);
    m_uniformMatrixFBO.modelview =  glm::mat4(1);
}
CScene::~CScene()
{
    delete m_pShader;
    delete m_pCamera;
    delete m_pFBO;

}
void    CScene::SetPerspective(GLfloat fov, GLfloat width, GLfloat height, GLfloat near, GLfloat far)
{
    m_uniformMatrix.projection = glm::perspective(fov, width/height, near, far);

    m_uniformMatrixFBO.projection=  glm::perspective(fov, (float)m_pFBO->GetLargeur()/m_pFBO->GetHauteur(),near,far);
}
void    CScene::Show(Uint32 elapsed, GLsizei width, GLsizei height)
{

    GLuint shaderID =   m_pShader->getProgramID();
    // camera
    m_pCamera->keyBoardEvent(*m_pCInput);
    m_pCamera->deplacer(*m_pCInput,elapsed);
    m_pCamera->lookAt(m_uniformMatrix.modelview);
    glUseProgram(shaderID);
    glEnable(GL_DEPTH_TEST);

		// light
		for (unsigned int i=0; i < m_pLight.size(); ++i)
			m_pLight[i]->SetShaderID(shaderID);

        m_uniformMatrix.modelviewLocation       =   glGetUniformLocation(shaderID, "modelview");
        m_uniformMatrix.mvpLocation             =   glGetUniformLocation(shaderID,"modelviewprojection");

        // FBO
        m_uniformMatrixFBO.modelviewLocation    =   glGetUniformLocation(shaderID, "modelview");
        m_uniformMatrixFBO.mvpLocation          =   glGetUniformLocation(shaderID,"modelviewprojection");

        // miroir
        glm::vec3 camPosition                   =   m_pCamera->GetPosition();
        glm::vec3 centre                        =   glm::vec3(0,0,0) + glm::vec3(0,0.5,0) + glm::vec3(0,0.5,0.5)
                                                     + glm::vec3(0,0,0.5) ;
        centre                                  += glm::vec3(-4,-1,0);
        glm::vec3   centerToCam                 =   camPosition - centre;
        glm::vec3   b1                          =   glm::vec3(0,0.5,0);
        glm::vec3   b2                          =   glm::vec3(0,0.5,0.5);
        glm::vec3   normal                      =   glm::cross(b1,b2);
        glm::normalize(normal);
        glm::normalize(centerToCam);

        //normal                                  =   (glm::dot(centerToCam,normal) > 0) ? normal : -normal;


        // calcul savant , cible = - centerToCam  + 2 * produitScalaire(centerToCam,normal) * normal
        // multiplier par -1 nous dis l'exp
        glm::vec3 cible                         =   -2 * glm::dot(centerToCam,normal) * normal + centerToCam;
        m_uniformMatrixFBO.modelview            =   glm::lookAt(glm::vec3(-4,-1,0), cible, glm::vec3(0,0,1));

        // the mirror reverse the image so in this case is Y axis
        m_uniformMatrixFBO.modelview            =   glm::scale(m_uniformMatrixFBO.modelview,glm::vec3(1.0,-1.0,1.0));
        glBindFramebuffer(GL_FRAMEBUFFER, m_pFBO->GetID());
            //glClearColor(1.0,1.0,1.0,1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // on redimensionne la zone d'affichage
            glViewport(0,0,m_pFBO->GetLargeur(), m_pFBO->GetHauteur());


            // rendu FBO
			// rendu light
			for (unsigned int i=0; i < m_pLight.size(); ++i)
			{
				// Seul la dernière light sera prise en compte
				m_pLight[i]->Show();
			}
            for (unsigned int i=0; i < m_pObject.size(); ++i)
            {
                m_pObject[i]->Show(m_uniformMatrixFBO, 2*elapsed);
            }
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        m_quad.SetIDTexture(m_pFBO->GetColorBufferID(0));
        // on revient dans la bonne dim
        glViewport(0,0,width,height);
		// rendu light

		for (unsigned int i=0; i < m_pLight.size(); ++i)
		{
			m_pLight[i]->Show();
			m_pLight[i]->SetEyeWorldPos(camPosition);
			m_pLight[i]->SetMatSpecularIntensity(1);
			m_pLight[i]->SetMatSpecularPower(32);
		}
        ShaderUniformMatrix intermed = m_uniformMatrix;
        intermed.modelview  =   glm::translate(intermed.modelview, glm::vec3(-4,-1,-1));
        intermed.modelview  =   glm::scale(intermed.modelview, glm::vec3(4,4,4));
		// on désactive le miroir pour l'instant
        //m_quad.Show(intermed,elapsed);

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
void	CScene::AttachLight(Light *light, const DirectionalLight &dl)
{
	light->SetDirectionalLight(dl);
	m_pLight.push_back(light);
}
void    CScene::AttachInput(CInput  *input)
{
    m_pCInput   =   input;
}

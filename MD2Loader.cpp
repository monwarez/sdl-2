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
#include "MD2Loader.h"
using namespace std;


// table de 162 vecteurs normaux précalculés
vec3_t CMD2Model::m_kAnorms[ NUMVERTEXNORMALS ] = {
#include    "Anorms.h"
};
CMD2Model::CMD2Model(const CMD2Model &model):m_kHeader(model.m_kHeader),m_fScale(model.m_fScale),m_texture(model.m_texture), m_vertice(model.m_vertice),
                                            m_texCoord(model.m_texCoord),m_normals(model.m_normals),m_ModelName(model.m_ModelName)
{
    m_pSkins                =   new md2_skin_t(*(model.m_pSkins));
    m_pTexCoords            =   new md2_texCoord_t(*(model.m_pTexCoords));
    m_pTriangles            =   new md2_triangle_t(*(model.m_pTriangles));
    m_pFrames               =   new md2_frame_t(*(model.m_pFrames));
    m_pGLcmds               =   new int (*(model.m_pGLcmds));
    m_isLoadMdl             =   model.m_isLoadMdl;



}
CMD2Model::CMD2Model()
{
    m_isLoadMdl     =   false;
}
CMD2Model::~CMD2Model()
{
    if (m_isLoadMdl)
        FreeModel();

    // sinon aucune allocation dynamique à gérer
}
bool CMD2Model::LoadModel(string szFilename)
{
    m_ModelName =   szFilename;
    fstream     file;

    file.open(szFilename.c_str(), ios::in | ios::binary);

    if (file.fail())
        return false;


    // lecture du header
    file.read((char*)&m_kHeader, sizeof(md2_header_t));

    // Vérification de l'authenticité du modèle

    if ( (m_kHeader.version != MD2_VERSION) || (m_kHeader.ident != MD2_IDENT) )
        return false;

    // allocations de mémoire pour les données du modèle

    m_pSkins        =   new md2_skin_t[m_kHeader.num_skins];
    m_pTexCoords    =   new md2_texCoord_t[m_kHeader.num_st];
    m_pTriangles    =   new md2_triangle_t[m_kHeader.num_tris];
    m_pFrames       =   new md2_frame_t[m_kHeader.num_frames];
    m_pGLcmds       =   new int[m_kHeader.num_glcmds];

    // lecture des noms des skins

    file.seekg(m_kHeader.offset_skins, ios::beg);
    file.read((char*) m_pSkins, sizeof(char) * 68 * m_kHeader.num_skins);

    // lecture des coordonnées de textures

    file.seekg(m_kHeader.offset_st, ios::beg);
    file.read((char*) m_pTexCoords, sizeof(md2_texCoord_t) * m_kHeader.num_st);

    // lecture des triangles

    file.seekg(m_kHeader.offset_tris, ios::beg);
    file.read((char*)m_pTriangles, sizeof(md2_triangle_t) * m_kHeader.num_tris);

    // lecture des frames
    file.seekg(m_kHeader.offset_frames, ios::beg);

    for (int i = 0; i < m_kHeader.num_frames; ++i)
    {

        // allocation de mémoire pour les vertices
        m_pFrames[i].verts      =   new md2_vertex_t[m_kHeader.num_vertices];

        // lecture des données de la frame
        file.read((char*)&m_pFrames[i].scale, sizeof (vec3_t));
        file.read((char*)&m_pFrames[i].translate, sizeof(vec3_t));
        file.read((char*)&m_pFrames[i].name, sizeof(char)*16);
        file.read((char*) m_pFrames[i].verts, sizeof(md2_vertex_t) * m_kHeader.num_vertices);
    }

    // lecture des commandes openGL
    file.seekg(m_kHeader.offset_glcmds, ios::beg);
    file.read((char*)m_pGLcmds, sizeof(int) * m_kHeader.num_glcmds);

    // fermeture du fichier
    file.close();

    // chargement du model réussi
    m_isLoadMdl = true;
    return true;
}
bool CMD2Model::LoadTexture(string szFilename)
{
    m_texture.setFilename(szFilename);
    if (m_texture.load())
        return true;

    return false;
}

void CMD2Model::LoadVBO()
{

    glGenBuffers(3, m_vboID);

    glGenVertexArrays(1,&m_vaoID);

    glBindVertexArray(m_vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);

            glBufferData(GL_ARRAY_BUFFER, (m_kHeader.num_tris* 9)  * sizeof(GLfloat), 0, GL_STREAM_DRAW);
            glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,m_vboID[1]);
            glBufferData(GL_ARRAY_BUFFER, (m_kHeader.num_tris* 6) * sizeof(GLfloat), 0, GL_STREAM_DRAW);
            glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER,m_vboID[2]);
            glBufferData(GL_ARRAY_BUFFER, (m_kHeader.num_tris* 9) * sizeof(GLfloat), 0, GL_STREAM_DRAW);
            glVertexAttribPointer(3,3,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(3);
    glBindVertexArray(0);

}

void CMD2Model::FreeModel()
{

    glDeleteBuffers(3, m_vboID);
    glDeleteVertexArrays(1,&m_vaoID);
    if( m_pSkins )
        delete [] m_pSkins;

    if( m_pTexCoords )
        delete [] m_pTexCoords;

    if( m_pTriangles )
        delete [] m_pTriangles;

    if( m_pFrames )
    {
        for( int i = 0; i < m_kHeader.num_frames; ++i )
        {
            if( m_pFrames[i].verts )
                delete [] m_pFrames[i].verts;
        }

        delete [] m_pFrames;
    }

}
void CMD2Model::RenderFrame(int iFrame)
{
    int     iMaxFrame   =   m_kHeader.num_frames - 1;

    m_texCoord.clear();
    m_vertice.clear();
    m_normals.clear();

    // vérification de la validité de la frame

    if ((iFrame < 0) || (iFrame > iMaxFrame))
        return;

    // création des tableaux de vertices , coordTex et normales associé à la frame
    int valprev = 0;
    for (int i = 0; i < m_kHeader.num_tris; ++i)
    {
        for (int k = 0; k < 3 ; ++k)
        {
            valprev += 8 * sizeof(GLfloat);
            md2_frame_t     *pFrame =   &m_pFrames[iFrame];
            md2_vertex_t    *pVert  =   &pFrame->verts[m_pTriangles[i].vertex[k]];

            // coordonnées de texture - attention il faut modifier le repère (la verticale)
            m_texCoord.push_back((GLfloat) m_pTexCoords[ m_pTriangles[i].st[k] ].s / m_kHeader.skinwidth);
            m_texCoord.push_back(-(GLfloat) m_pTexCoords[ m_pTriangles[i].st[k] ].t / m_kHeader.skinheight);

            // normales
            m_normals.push_back(m_kAnorms[pVert->normalIndex][0]);
            m_normals.push_back(m_kAnorms[pVert->normalIndex][1]);
            m_normals.push_back(m_kAnorms[pVert->normalIndex][2]);

            // et maintenant les sommets
            m_vertice.push_back(pFrame->scale[0] * pVert->v[0] + pFrame->translate[0]* m_fScale);
            m_vertice.push_back(pFrame->scale[1] * pVert->v[1] + pFrame->translate[1]* m_fScale);
            m_vertice.push_back(pFrame->scale[2] * pVert->v[2] + pFrame->translate[2]* m_fScale);
        }

    }
    unsigned int nbTris = m_vertice.size()/3;
    m_sSommets    =   m_vertice.size() * sizeof(GLfloat);
    m_sCoord      =   m_texCoord.size() * sizeof(GLfloat);
    m_sNormals    =   m_normals.size() * sizeof(GLfloat);


    this->UpdateVBO();
    m_vertice.clear();
    m_texCoord.clear();

    m_normals.clear();

    glBindVertexArray(m_vaoID);
        glBindTexture(GL_TEXTURE_2D, m_texture.getID());
        glDrawArrays(GL_TRIANGLES, 0, nbTris);
        glBindTexture(GL_TEXTURE_2D,0);

    glBindVertexArray(m_vaoID);
    GL_CHECK;
}
void CMD2Model::UpdateVBO()
{
    glBindVertexArray(m_vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);

            void *adresseVBO    =   NULL;

            adresseVBO          =   glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);


            if (adresseVBO == NULL)
                throw GEST_ERROR("le vbo est pointeur null - vertices");

            memcpy(adresseVBO, &m_vertice[0], m_sSommets);
            glUnmapBuffer(GL_ARRAY_BUFFER);

            glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,m_vboID[1]);
            adresseVBO          =   glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
            if (adresseVBO == NULL)
                throw GEST_ERROR("le vbo est pointeur null - textureCoord0");

            memcpy(adresseVBO, &m_texCoord[0], m_sCoord);
            glUnmapBuffer(GL_ARRAY_BUFFER);

            glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER,m_vboID[2]);
            adresseVBO          =   glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
            if (adresseVBO == NULL)
                throw GEST_ERROR("le vbo est pointeur null - normals");

            memcpy(adresseVBO, &m_normals[0], m_sNormals);
            glUnmapBuffer(GL_ARRAY_BUFFER);

            glVertexAttribPointer(3,3,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}
void CMD2Model::DrawModelItp(int iFrameA, int iFrameB, float fInterp)
{

    int iMaxFrame       =   m_kHeader.num_frames - 1;
    if ((iFrameA < 0) || (iFrameB < 0))
        return;

    if ((iFrameA > iMaxFrame) || (iFrameB > iMaxFrame))
        return;
    m_vertice.clear();
    m_texCoord.clear();
    m_normals.clear();


    // création des différends tableaux
    for (int i = 0; i < m_kHeader.num_tris; ++i)
    {
        for (int k = 0; k < 3; ++k)
        {
            md2_frame_t *pFrameA    =   &m_pFrames[iFrameA];
            md2_frame_t *pFrameB    =   &m_pFrames[iFrameB];

            md2_vertex_t *pVertA = &pFrameA->verts[ m_pTriangles[i].vertex[k] ];
            md2_vertex_t *pVertB = &pFrameB->verts[ m_pTriangles[i].vertex[k] ];

            // [coordonnées de texture]
            m_texCoord.push_back( (GLfloat)m_pTexCoords[ m_pTriangles[i].st[k] ].s / m_kHeader.skinwidth);
            m_texCoord.push_back(-(GLfloat)m_pTexCoords[ m_pTriangles[i].st[k] ].t / m_kHeader.skinheight);

            // [normale]
            vec3_t normA, normB;

            memcpy( normA, m_kAnorms[ pVertA->normalIndex ], 3 * sizeof( float ) );
            memcpy( normB, m_kAnorms[ pVertB->normalIndex ], 3 * sizeof( float ) );

            // interpolation linéaire
            m_normals.push_back( normA[0] + fInterp * (normB[0] - normA[0]));
            m_normals.push_back( normA[1] + fInterp * (normB[1] - normA[1]));
            m_normals.push_back( normA[2] + fInterp * (normB[2] - normA[2]));

            // [vertex]
                vec3_t vecA, vecB;

            // calcul de la position absolue des vertices
            vecA[0] = pFrameA->scale[0] * pVertA->v[0] + pFrameA->translate[0];
            vecA[1] = pFrameA->scale[1] * pVertA->v[1] + pFrameA->translate[1];
            vecA[2] = pFrameA->scale[2] * pVertA->v[2] + pFrameA->translate[2];

            vecB[0] = pFrameB->scale[0] * pVertB->v[0] + pFrameB->translate[0];
            vecB[1] = pFrameB->scale[1] * pVertB->v[1] + pFrameB->translate[1];
            vecB[2] = pFrameB->scale[2] * pVertB->v[2] + pFrameB->translate[2];

            // interpolation linéaire et redimensionnement
            m_vertice.push_back( (vecA[0] + fInterp * (vecB[0] - vecA[0])) * m_fScale);
            m_vertice.push_back( (vecA[1] + fInterp * (vecB[1] - vecA[1])) * m_fScale);
            m_vertice.push_back( (vecA[2] + fInterp * (vecB[2] - vecA[2])) * m_fScale);
        }

    }
    // maintenant , il suffit d'afficher
    unsigned int nbTris = m_vertice.size()/3;

    m_sSommets      =   m_vertice.size() * sizeof(GLfloat);
    m_sCoord        =   m_texCoord.size() * sizeof(GLfloat);
    m_sNormals      =   m_normals.size() * sizeof(GLfloat);

    this->UpdateVBO();
    m_vertice.clear();
    m_texCoord.clear();

    m_normals.clear();



    glBindVertexArray(m_vaoID);
        glBindTexture(GL_TEXTURE_2D, m_texture.getID());
        glDrawArrays(GL_TRIANGLES, 0, nbTris);
        glBindTexture(GL_TEXTURE_2D,0);

    glBindVertexArray(0);
}
// ----------------------------------------------
// RenderFrameWithGLcmds() - dessine le modèle à
// la frame spécifiée en utilisant les commandes
// OpenGL.
// ----------------------------------------------

void CMD2Model::RenderFrameWithGLcmds( int iFrame )
{
    this->RenderFrame(iFrame);
}
// --------------------------------------------------------------------------
// CMD2Model::drawModelItpWithGLcmds
//
// Render the model with frame interpolation, using OpenGL commands.
// --------------------------------------------------------------------------

void
CMD2Model::DrawModelItpWithGLcmds (int frameA, int frameB, float interp)
{

    this->DrawModelItp(frameA,frameB,interp);

}
CEntity::CEntity():m_fInterp(1.0),m_fPercent(0),m_fScale(1.0)
{

}
// ----------------------------------------------
// Animate() - calcul les frames courante et
// suivante à partir des frames de début et de
// fin d'animation et du pourcentage d'interpolation.
// ----------------------------------------------

void CEntity::Animate( int iStartFrame, int iEndFrame, float fPercent )
{
    // m_iCurrFrame doit être compris entre iStartFrame et iEndFrame
    if( m_iCurrFrame < iStartFrame )
        m_iCurrFrame = iStartFrame;

    if( m_iCurrFrame > iEndFrame )
        m_iCurrFrame = iStartFrame;

    m_fPercent = fPercent;

    // animation : calcul des frames courante et suivante
    if( m_fInterp >= 1.0 )
    {
        m_fInterp = 0.0f;
        m_iCurrFrame++;

        if( m_iCurrFrame >= iEndFrame )
            m_iCurrFrame = iStartFrame;

        m_iNextFrame = m_iCurrFrame + 1;

        if( m_iNextFrame >= iEndFrame )
            m_iNextFrame = iStartFrame;
    }
}
// ----------------------------------------------
// DrawEntity() - dessine le modèle de l'entitée.
// si le modèle n'est pas animé, on dessine la
// frame iFrame. Si cette dernière est négative,
// on dessine la frame courante.
// ----------------------------------------------

void CEntity::DrawEntity( int iFrame, bool bAnimated, bool bUseGLCmds )
{
    // redimensionnement du modèle
    m_pModel->SetScale( m_fScale );

    // rendu du modèle
    if( bAnimated )
    {
        if (bUseGLCmds)
        {
            // dessine chaque triangle du modèle avec commandes openGL
            m_pModel->DrawModelItpWithGLcmds( m_iCurrFrame, m_iNextFrame, m_fInterp );
        }
        else
        {
            // dessine chaque triangle du modèle
            m_pModel->DrawModelItp( m_iCurrFrame, m_iNextFrame, m_fInterp );
        }
        // incrémentation du pourcentage d'interpolation entre les deux frames
        m_fInterp += m_fPercent;
    }
    else
    {
        if (bUseGLCmds)
        {
            // dessine chaque triangle du modèle
            if( iFrame < -1 )
                m_pModel->RenderFrameWithGLcmds( m_iCurrFrame );
            else
                m_pModel->RenderFrameWithGLcmds( iFrame );

        }
        else
        {
            // dessine chaque triangle du modèle
            if( iFrame == -1 )
                m_pModel->RenderFrame( m_iCurrFrame );
            else
                m_pModel->RenderFrame( iFrame );
        }

    }

}

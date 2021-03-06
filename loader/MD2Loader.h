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
#ifndef MD2LOADER_H_INCLUDED
#define MD2LOADER_H_INCLUDED

#include <GL/glew.h> // glew for all platform

#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory.h>
#include "../graphic/Texture.h"
#include "../util/DebugGL.h"

#define NUMVERTEXNORMALS        162
// identifiant "IDP2" ou 844121161
#define MD2_IDENT               (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// num�ro de version
#define MD2_VERSION             8

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif


// header md2
typedef struct
{
    int ident;          // num�ro magique : "IDP2"
    int version;        // version du format : 8

    int skinwidth;      // largeur texture
    int skinheight;     // hauteur texture

    int framesize;      // taille d'une frame en octets

    int num_skins;      // nombre de skins
    int num_vertices;   // nombre de vertices par frame
    int num_st;         // nombre de coordonn�es de texture
    int num_tris;       // nombre de triangles
    int num_glcmds;     // nombre de commandes opengl
    int num_frames;     // nombre de frames

    int offset_skins;   // offset donn�es skins
    int offset_st;      // offset donn�es coordonn�es de texture
    int offset_tris;    // offset donn�es triangles
    int offset_frames;  // offset donn�es frames
    int offset_glcmds;  // offset donn�es commandes OpenGL
    int offset_end;     // offset fin de fichier

} md2_header_t;
typedef float vec3_t[3];

typedef struct
{
    unsigned char   v[3];
    unsigned char   normalIndex;
}md2_vertex_t;

typedef struct
{
    unsigned short  vertex[3];
    unsigned short  st[3];
}md2_triangle_t;

typedef struct
{
    short           s;
    short           t;
}md2_texCoord_t;

typedef struct
{
    vec3_t          scale;
    vec3_t          translate;
    char            name[16]; // nom  de la frame
    md2_vertex_t    *verts;
}md2_frame_t;
typedef struct
{
    char            name[68];
}md2_skin_t;

// commande OpenGL
typedef struct
{
    float   s;          // coordonn�e de texture s
    float   t;          // coordonn�e de texture t
    int     index;      // index vertex

} md2_glcmd_t;

class CMD2Model
{
    public:

        CMD2Model();
        CMD2Model(const CMD2Model &model);
        ~CMD2Model();

        bool        LoadModel(std::string szFilename);
        bool        LoadTexture(std::string szFilename);
        void        LoadVBO();
        void        FreeModel();

        void        RenderFrame(int iFrame);
        void        DrawModelItp(int iFrameA, int iFrameB, float fInterp);
        void        RenderFrameWithGLcmds( int iFrame );
        void        DrawModelItpWithGLcmds (int frameA, int frameB, float interp);
        void        SetScale(GLfloat fscale){m_fScale = fscale;};

        GLfloat     GetScaleValue(){return m_fScale;}
        std::string GetModelName(){return m_ModelName;}

    protected:
        void        UpdateVBO();
        static vec3_t           m_kAnorms[NUMVERTEXNORMALS];

        md2_header_t            m_kHeader;      //  header md2
        md2_skin_t              *m_pSkins;      //  donn�es skins
        md2_texCoord_t          *m_pTexCoords;  //  coordonn�es de textures
        md2_triangle_t          *m_pTriangles;  //  donn�es triangles
        md2_frame_t             *m_pFrames;     //  donn�es frames
        int                     *m_pGLcmds;     //  liste de commandes openGL

        GLfloat                 m_fScale;       //  redimensionnement du mod�le

        Texture                 m_texture;      //  texture

        std::vector<GLfloat>    m_vertice;
        std::vector<GLfloat>    m_texCoord;
        std::vector<GLfloat>    m_normals;

        std::string             m_ModelName;
        GLuint                  m_vboID[3];
        GLuint                  m_vaoID;
        GLuint                  m_sSommets;
        GLuint                  m_sNormals;
        GLuint                  m_sCoord;

        // bool�en pour �viter un crash , en effet si on a jamais charg� de mod�le , le destructeur ne doit pas �tre lanc�
        bool                    m_isLoadMdl;


};


// Class CEntity
class CEntity
{

    public:
        CEntity();
        ~CEntity() {}


        void    SetModel(CMD2Model *pModel) {m_pModel = pModel;}

        void    DrawEntity(int iFrame , bool bAnimated, bool bUseGLCmds);
        void    Animate(int iStartFrame, int iEndFrame, float fPercent);

        void    SetScale(float fScale) {m_fScale = fScale;}
        float   GetScaleValue(){return m_fScale;}

    protected:
        CMD2Model       *m_pModel;

        int             m_iCurrFrame;
        int             m_iNextFrame;
        float           m_fInterp;          //  pourcentage interpolation

        float           m_fPercent;         //  incr�mentation de m_fInterp
        float           m_fScale;


};
#endif // MD2LOADER_H_INCLUDED

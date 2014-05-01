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
#include "AssimpLoad.h"
#include <fstream>
AssimpLoad::AssimpLoad(const std::string &filename)
{
	 // Create an instance of the Importer class
	Assimp::Importer	importer;

	scene 				= importer.ReadFile(filename, 	aiProcess_CalcTangentSpace 		|
														aiProcess_Triangulate		 	|
														aiProcess_JoinIdenticalVertices	|
														aiProcess_SortByPType);
	// check if file exists
	std::ifstream fin(filename.c_str());
	if(!fin.fail())
		fin.close();
	else
		GEST_ERROR("Le fichier: " + filename + "n'est pas accessible ");
	if ( ! scene )
	{
		GEST_ERROR(importer.GetErrorString() );
	}

	// access file's contents
	// texture informations
	for (unsigned int i=0; i < scene->mNumMaterials;++i)
	{
		int 		texIndex	=	0;
		aiReturn	texFound	=	AI_SUCCESS;

		aiString	path;

		while(AI_SUCCESS == texFound)
		{
			texFound 	=	scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
			m_textureIdMap[path.data] = NULL ; 
			++texIndex;
		}
	}

	
	


}
AssimpLoad::~AssimpLoad()
{
	// destroy allocated things
}
void	AssimpLoad::Show() // for now , the number of param was unknow
{
}

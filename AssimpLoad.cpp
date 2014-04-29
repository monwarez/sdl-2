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
AssimpLoad::AssimpLoad(const std::string &filename)
{
	 // Create an instance of the Importer class
	Assimp::Importer	importer;

	const aiScene* scene = importer.ReadFile(filename, 	aiProcess_CalcTangentSpace 		|
														aiProcess_Triangulate		 	|
														aiProcess_JoinIdenticalVertices	|
														aiProcess_SortByPType);
	if ( ! scene )
	{
		GEST_ERROR(importer.GetErrorString() );
	}

	// access file's contents

}
AssimpLoad::~AssimpLoad()
{
	// destroy allocated things
}
void	AssimpLoad::Show() // for now , the number of param was unknow
{
}

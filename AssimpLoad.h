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
#ifndef ASSIMPLOAD_H_INCLUDED
#define ASSIMPLOAD_H_INCLUDED
#include "Texture.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

class AssimpLoad
{

	public:
		AssimpLoad(const std::string &filename);
		~AssimpLoad();

		virtual	void 	Show() ; // pour l'instant les paramètres ne sont pas encore définits
	protected:
		Texture		texture;
};
#endif // ASSIMPLOAD_H_INCLUDED

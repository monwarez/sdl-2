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
#ifndef GLM_FORCE_RADIANS
	#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLEW for all platform
#include <GL/glew.h>
struct DirectionalLight
{
	glm::vec3	Color;
	GLfloat		AmbientIntensity;
	glm::vec3	Direction;
	GLfloat		DiffuseIntensity;
};

class Light
{
	public:
		Light();
		virtual	void	Show();
		virtual void 	SetDirectionalLight(const DirectionalLight &light);
		virtual	void	SetShaderID(GLuint shaderID);

	protected:
		DirectionalLight	m_dlight;
		//GLuint				m_WVPLocation;
		//GLuint				m_samplerLocation;
		GLuint				m_dirLightColorLocation;
		GLuint				m_dirLightAmbientIntensityLocation;
		GLuint				m_dirLightDirectionLocation;
		GLuint				m_dirLightDiffuseIntensityLocation;
};

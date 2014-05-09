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
#include "Light.h"

Light::Light()
{
	
}
void	Light::SetDirectionalLight(const DirectionalLight &light)
{
	m_dlight	=	light;
}
void	Light::Show()
{
	// sendind light information
	glUniform3f(m_dirLightColorLocation, m_dlight.Color.x, m_dlight.Color.y, m_dlight.Color.z);
	glUniform1f(m_dirLightAmbientIntensityLocation, m_dlight.AmbientIntensity);
}
void	Light::SetShaderID(GLuint shaderID)
{
	// Get the location of the light uniform in the shader
	m_dirLightColorLocation				=	glGetUniformLocation(shaderID,"directionalLight.Color");
	m_dirLightAmbientIntensityLocation	=	glGetUniformLocation(shaderID,"directionalLight.AmbientIntensity");

}

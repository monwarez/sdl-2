// Version du GLSL

#version 150


// Entrée

in vec2 coordTexture;

// pour les lumières
struct DirectionalLight
{
	vec3 	Color;
	float	AmbientIntensity;
};
// Uniform

uniform sampler2D tex0;
uniform DirectionalLight	directionalLight;

// Sortie 

// layout (location = 0) out vec4 out_Color; // for 330 and more
out vec4 out_Color;


// Fonction main

void main()
{
	
	
	out_Color 	=	texture(tex0,coordTexture.xy)*vec4(directionalLight.Color,1.0f)* directionalLight.AmbientIntensity ;
	 
}

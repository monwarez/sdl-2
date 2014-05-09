// Version du GLSL

#version 150


// Entrée

in vec2 coordTexture;
in vec3	Normal0;
// pour les lumières
struct DirectionalLight
{
	vec3 	Color;
	float	AmbientIntensity;
	float	DiffuseIntensity;
	vec3	Direction;
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
	// Ambient color
	vec4 ambientColor	=	vec4(directionalLight.Color,1.0f)*directionalLight.AmbientIntensity;
	// Diffuse factor
	float diffuseFactor	=	dot(normalize(Normal0), -directionalLight.Direction);
	vec4	diffuseColor;
	if (diffuseFactor > 0)
	{
		diffuseColor	=	vec4(directionalLight.Color,1.0f)*directionalLight.DiffuseIntensity*diffuseFactor;
	}
	else
	{
		diffuseColor	=	vec4(0,0,0,0);
	}
	
	out_Color 	=	texture(tex0,coordTexture.xy)*(ambientColor + diffuseColor) ;
	 
}

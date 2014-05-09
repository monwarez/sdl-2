// Version du GLSL

//#version 150 core
#version 120

// Entrée

varying vec2 	coordTexture;
varying vec3 	Normal0;

// Uniform

uniform sampler2D text;

// Light
struct DirectionalLight
{
	vec3 	Color;
	float	AmbientIntensity;
	float	DiffuseIntensity;
	vec3	Direction;
};
uniform DirectionalLight directionalLight;


// Fonction main

void main()
{
	// Ambient color
	vec4 	ambientColor	=	vec4(directionalLight.Color,1.0f)*directionalLight.AmbientIntensity;
	// diffuse factor
	float diffuseFactor		=	dot(normalize(Normal0), -directionalLight.Direction);
	vec4 diffuseColor;
	if (diffuseFactor > 0)
	{
		diffuseColor = vec4(directionalLight.Color, 1.0f)* directionalLight.DiffuseIntensity*diffuseFactor;
	}
	else
	{
		diffuseColor = vec4(0,0,0,0);
	}
	
    // Couleur du pixel
    gl_FragColor = texture2D(text, coordTexture)* (ambientColor + diffuseColor);
}

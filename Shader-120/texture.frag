// Version du GLSL

//#version 150 core
#version 120

// Entrée

varying vec2 	coordTexture;
varying vec3 	Normal0;
varying vec3	WorldPos0;
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
uniform DirectionalLight 	directionalLight;
uniform vec3				eyeWorldPos;
uniform float				matSpecularIntensity;
uniform float				matSpecularPower;

// Fonction main

void main()
{
	// Ambient color
	vec4 	ambientColor	=	vec4(directionalLight.Color,1.0f)*directionalLight.AmbientIntensity;
	vec3	LightDirection	=	-directionalLight.Direction;
	vec3	Normal			=	normalize(Normal0);
	// diffuse factor
	float diffuseFactor		=	dot(Normal, LightDirection);
	vec4 diffuseColor		=	vec4(0,0,0,0);
	vec4 specularColor		=	vec4(0,0,0,0);
	if (diffuseFactor > 0)
	{
		diffuseColor = vec4(directionalLight.Color, 1.0f)* directionalLight.DiffuseIntensity*diffuseFactor;
		vec3	VertexToEye		=	normalize(eyeWorldPos - WorldPos0);
		vec3	LightReflect	=	normalize(reflect(directionalLight.Direction, Normal));
		float	SpecularFactor	=	dot (VertexToEye, LightReflect);
		SpecularFactor			=	pow(SpecularFactor,matSpecularPower);
		if (SpecularFactor > 0)
		{
			specularColor	=	vec4(directionalLight.Color,1.0f)*matSpecularIntensity*SpecularFactor;
		}
	}
	
	
    // Couleur du pixel
    gl_FragColor = texture2D(text, coordTexture)* (ambientColor + diffuseColor + specularColor)  ;
}

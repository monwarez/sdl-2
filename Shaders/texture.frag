// Version du GLSL

#version 330


// Entrée

in vec2 coordTexture;

// pour les lumières
in vec3 vNormal;
in vec3 veye;
in vec3 vPosition;
in vec3 rayon;

in vec4 vAmbiant;
in vec4 vDiffuse;
in vec4 vSpecular;

in float shininess;
in float intensity;
// Uniform

uniform sampler2D tex0;


// Sortie 

layout (location = 0) out vec4 out_Color;


// Fonction main

void main()
{
	
	
	out_Color 	=	texture(tex0,coordTexture.xy) ;
	 
}

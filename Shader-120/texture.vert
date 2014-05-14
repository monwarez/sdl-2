// Version du GLSL

//#version 150 core
#version 120 

// Entres

attribute vec3 in_Vertex;
attribute vec2 in_TexCoord0;
attribute vec3 in_Normal;

// Uniform

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 modelviewprojection;

// Sortie

varying vec2 	coordTexture;
varying vec3	Normal0;
varying vec3	WorldPos0;
// Fonction main

void main()
{
    // Position finale du vertex en 3D

    gl_Position = modelviewprojection * vec4(in_Vertex, 1.0);


    // Envoi des coordonnes de texture au Fragment Shader
	coordTexture = in_TexCoord0;
	//gl_TexCoord[0].st = in_TexCoord0;
	// calcul de Normal0
	Normal0	=	(modelview	*	vec4(in_Normal, 0.0)).xyz;
	WorldPos0=	(modelview 	*	vec4(in_Vertex, 1.0)).xyz;
}

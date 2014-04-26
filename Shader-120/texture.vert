// Version du GLSL

//#version 150 core
#version 120

// Entrées

attribute vec3 in_Vertex;
attribute vec3 in_Color;
attribute vec2 in_TexCoord0;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 modelviewprojection;

// Sortie

varying vec2 coordTexture;

// Fonction main

void main()
{
    // Position finale du vertex en 3D

    gl_Position = modelviewprojection * vec4(in_Vertex, 1.0);


    // Envoi des coordonnées de texture au Fragment Shader
	coordTexture = in_TexCoord0;
	//gl_TexCoord[0].st = in_TexCoord0;
}

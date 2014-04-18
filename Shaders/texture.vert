// Version du GLSL

#version 150


// Entrées
// for 330 and more
//layout (location = 0) in vec3 in_Vertex;
//layout (location = 2) in vec2 in_TexCoord0;
//layout (location = 3) in vec3 in_Normals;

// compatibility for 150 - ie Mac OS X
in vec3 in_Vertex;
in vec2 in_TexCoord0;
in vec3 in_Normals;
// Uniform

uniform mat4 modelviewprojection;

// pour les lumières
// normal matrix
//uniform mat3 normal_matrix
// ne marche pas
uniform mat4 lookAt;
uniform mat4 modelview;
uniform vec3 lPosition;
uniform vec3 lDirection;

uniform vec4 lAmbiant;
uniform vec4 lDiffuse;
uniform vec4 lSpecular;

uniform float lShininess;
uniform float lIntensity;
// Sortie

out vec2 coordTexture;

// pour les lumières
out vec3 vNormal;
out vec3 veye;
out vec3 vPosition;

out vec4 vAmbiant;
out vec4 vDiffuse;
out vec4 vSpecular;
out vec3 rayon;
out float shininess;
out float intensity;
// Fonction main

void main()
{
	vAmbiant	= lAmbiant;
	vDiffuse 	= lDiffuse;
	vSpecular	= lSpecular;
	vPosition	= lPosition;
	shininess	= lShininess;
	intensity 	= lIntensity;
	
	// peu sur
	vNormal		= in_Normals;
	
    // Position finale du vertex en 3D

    gl_Position = modelviewprojection * vec4(in_Vertex, 1.0);
	//vec3 vVertex	=	(modelview*vec4(in_Vertex,1.0)).xyz;
	//rayon 	=	normalize((lookAt*vec4(lPosition,1.0)).xyz);
	//rayon 	= 	normalize((lookAt*vec4(lPosition,1.0)).xyz - vVertex);
	//veye 	=	normalize(-vVertex);
	
    // Envoi des coordonnées de texture au Fragment Shader

    coordTexture = in_TexCoord0;

}

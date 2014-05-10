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
in vec3 in_Normal;
// Uniform

uniform mat4 modelviewprojection;
uniform mat4 projection;
// pour les lumières
uniform mat4 modelview;

// Sortie

out vec2 	coordTexture;
out vec3	WorldPos0;
// pour les lumières
out vec3 Normal0;
// Fonction main

void main()
{
    // Position finale du vertex en 3D
    gl_Position = modelviewprojection * vec4(in_Vertex, 1.0);
	
    // Envoi des coordonnées de texture au Fragment Shader

    coordTexture 	= 	in_TexCoord0;
	Normal0			=	(modelview * vec4(in_Normal,0.0)).xyz;
	WorldPos0		=	(modelview * vec4(in_Vertex,1.0)).xyz;
}

// Version du GLSL

#version 120 


// Entrées
uniform mat4 modelview;
uniform mat4 projection;
uniform mat4 promov;
// Sortie

varying vec4 out_color;

// Fonction main

void main()
{
    	// Position finale du vertex

	gl_Position = promov * gl_Vertex;


    	// Envoi de la couleur au Fragment Shader
	out_color = gl_Color;
}

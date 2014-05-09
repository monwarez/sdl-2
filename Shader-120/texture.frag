// Version du GLSL

//#version 150 core
#version 120

// Entrée

varying vec2 coordTexture;


// Uniform

uniform sampler2D text;

// Light
struct DirectionalLight
{
	vec3 	Color;
	float	AmbientIntensity;
};
uniform DirectionalLight directionalLight;


// Fonction main

void main()
{
    // Couleur du pixel

    gl_FragColor = texture2D(text, coordTexture)* vec4(directionalLight.Color,1.0f)* directionalLight.AmbientIntensity;
}

// Version du GLSL

//#version 150 core
#version 120

// Entrée

varying vec2 coordTexture;


// Uniform

uniform sampler2D text;


// Sortie 


// Fonction main

void main()
{
    // Couleur du pixel

    gl_FragColor = texture2D(text, coordTexture);
}

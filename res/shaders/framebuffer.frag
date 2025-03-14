#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform float width;
uniform float height;

uniform sampler2D screenTexture;

void main()
{	
    FragColor = texture(screenTexture, texCoords);
}
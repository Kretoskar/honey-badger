#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 DepthColor;

in vec3 texCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, texCoords);
	DepthColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
}
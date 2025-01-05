#version 330 core
out vec4 FragColor;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 DepthColor;

in vec2 texUV;

uniform sampler2D diffuseMap;

void main()
{
    FragColor = vec4(color.x, color.y, color.z, 1.0f);
	DepthColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
}
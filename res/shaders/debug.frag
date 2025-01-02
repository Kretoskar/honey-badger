#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 DepthColor;

in vec3 color;

void main()
{
    FragColor = vec4(color.r, color.g, color.b, 1.0f);
	DepthColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
}
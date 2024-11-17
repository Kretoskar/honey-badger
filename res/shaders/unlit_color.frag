#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texUV;

uniform sampler2D diffuseMap;

void main()
{
    FragColor = vec4(color.x, color.y, color.z, 1.0f);
}
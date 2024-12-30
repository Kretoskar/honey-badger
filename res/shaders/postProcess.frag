#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform float width;
uniform float height;

uniform sampler2D screenTexture;

void make_luminance_kernel(inout float n[9], sampler2D tex, vec2 coord, float w, float h)
{
	vec4 texCoord = texture2D(tex, coord + vec2( -w, -h));
	n[0] = texCoord.r * 0.299 + texCoord.g * 0.587 + texCoord.b * 0.114;
	
	texCoord = texture2D(tex, coord + vec2(0.0, -h));
	n[1] = texCoord.r * 0.299 + texCoord.g * 0.587 + texCoord.b * 0.114;
	
	texCoord = texture2D(tex, coord + vec2(  w, -h));
	n[2] = texCoord.r * 0.299 + texCoord.g * 0.587 + texCoord.b * 0.114;
	
	texCoord = texture2D(tex, coord + vec2(  -w, 0.0));
	n[3] = texCoord.r * 0.299 + texCoord.g * 0.587 + texCoord.b * 0.114;
	
	texCoord = texture2D(tex, coord);
	n[4] = texCoord.r * 0.299 + texCoord.g * 0.587 + texCoord.b * 0.114;
	
	texCoord = texture2D(tex, coord + vec2(  w, 0.0));
	n[5] = texCoord.r * 0.299 + texCoord.g * 0.587 + texCoord.b * 0.114;
	
	texCoord = texture2D(tex, coord + vec2(  -w, h));
	n[6] = texCoord.r * 0.299 + texCoord.g * 0.587 + texCoord.b * 0.114;
	
	texCoord = texture2D(tex, coord + vec2(  0.0, h));
	n[7] = texCoord.r * 0.299 + texCoord.g * 0.587 + texCoord.b * 0.114;
	
	texCoord = texture2D(tex, coord + vec2(  w, h));
	n[8] = texCoord.r * 0.299 + texCoord.g * 0.587 + texCoord.b * 0.114;
}

float sobel(float n[9])
{
	float sobelV = -n[0] + n[2] + -2.0 * n[3] + 2.0 * n[5] - n[6] + n[8];
	float sobelH = -n[0] - 2.0 * n[1] - n[2] + n[6] + 2.0 * n[7] + n[8];
	return sqrt((sobelH * sobelH) + (sobelV * sobelV));
}

void make_kernel(inout vec4 n[9], sampler2D tex, vec2 coord, float w, float h)
{
	n[0] = texture2D(tex, coord + vec2( -w, -h));
	n[1] = texture2D(tex, coord + vec2(0.0, -h));
	n[2] = texture2D(tex, coord + vec2(  w, -h));
	n[3] = texture2D(tex, coord + vec2( -w, 0.0));
	n[4] = texture2D(tex, coord);
	n[5] = texture2D(tex, coord + vec2(  w, 0.0));
	n[6] = texture2D(tex, coord + vec2( -w, h));
	n[7] = texture2D(tex, coord + vec2(0.0, h));
	n[8] = texture2D(tex, coord + vec2(  w, h));
}

vec4 boxBlur(vec4 n[9])
{
	vec4 ret = vec4(0.0, 0.0, 0.0, 0.0);
	
	for (int i = 0; i < 9; i++)
	{
		ret += n[i] / 9.0;
	}
	
	return ret;
}

void main()
{
	float n[9];
	make_luminance_kernel(n, screenTexture, texCoords, 1.0 / (width), 1.0 / (height));
	float s = sobel(n);
	
	float w[9];
	make_luminance_kernel(w, screenTexture, texCoords, 1.0 / (width / 2), 1.0 / (height / 2));
	float ws = sobel(w);
	
	float ww[9];
	make_luminance_kernel(ww, screenTexture, texCoords, 1.0 / (width / 3), 1.0 / (height / 3));
	float wws = sobel(ww);
	
	vec4 color;
	if (s > 0.1)
	{
		color = vec4(0.0, 0.0, 0.0, 0.9);
	}
	else if (ws > 0.1)
	{
		color = vec4(0.0, 0.0, 0.0, 0.6);
	}
	else if (wws > 0.1)
	{
		color = vec4(0.0, 0.0, 0.0, 0.2);
	}
	else 
	{
		color = vec4(0.0, 0.0, 0.0, 0.0);
	}
	
    FragColor = color;
}
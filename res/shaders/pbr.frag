#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 DepthColor;

in vec3 pos;
in vec3 normal;
in vec3 color;
in vec2 texUV;

uniform sampler2D diffuseMap;

uniform float ambient;
uniform float diffuseIntensity;
uniform vec4 lightColor;
uniform vec3 lightDir;
uniform vec3 cameraPos;

const int bands = 4;
const float toonColorFactor = 1.0f / bands;

float CalcRimLightFactor(vec3 PixelToCamera, vec3 Normal)
{
	float RimFactor = dot (PixelToCamera, Normal);
	RimFactor = 1 - RimFactor;
	RimFactor = max(0.0, RimFactor);
	RimFactor = pow(RimFactor, 2.0);
	return RimFactor;
}

float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}


void main()
{    
    // diffuse lighting
    vec3 normal = normalize(normal);
    vec3 lightDirection = normalize(lightDir);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
	diffuse = ceil(diffuse * bands) * toonColorFactor;
	
	vec3 viewDirection = normalize(cameraPos - pos);
	
	// specular lighting
	float specular = 0.0f;
    if (diffuse != 0.0f)
    {
        float specularLight = 0.50f;
        
        vec3 halfwayVec = normalize(viewDirection + lightDirection);
        float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
        specular = specAmount * specularLight;
		specular = ceil(specular * bands) * toonColorFactor;
    }

	vec4 diffuseColor = texture(diffuseMap, texUV);
	//vec4 RimColor = diffuseColor * CalcRimLightFactor(viewDirection, normal);
	vec4 finalColor = diffuseColor * lightColor * (diffuse * diffuseIntensity + ambient + specular);
	
	
	
    FragColor = vec4(finalColor.r, finalColor.g, finalColor.b, diffuseColor.a);
	DepthColor = vec4(vec3(linearizeDepth(gl_FragCoord.z) / far), 1.0f);
}
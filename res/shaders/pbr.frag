#version 330 core
out vec4 FragColor;

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

const int bands = 1;
const float toonColorFactor = 1.0f / bands;

float CalcRimLightFactor(vec3 PixelToCamera, vec3 Normal)
{
	float RimFactor = dot (PixelToCamera, Normal);
	RimFactor = 1 - RimFactor;
	RimFactor = max(0.0, RimFactor);
	RimFactor = pow(RimFactor, 2.0);
	return RimFactor;
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
    }

	vec4 diffuseColor = texture(diffuseMap, texUV);
	//vec4 RimColor = diffuseColor * CalcRimLightFactor(viewDirection, normal);
	vec4 finalColor = diffuseColor * lightColor * (diffuse * diffuseIntensity + ambient + specular);
	
    FragColor = vec4(finalColor.r, finalColor.g, finalColor.b, diffuseColor.a);
}
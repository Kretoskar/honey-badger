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

void main()
{    
    // diffuse lighting
    vec3 normal = normalize(normal);
    vec3 lightDirection = normalize(lightDir);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
	
	// specular lighting
	float specular = 0.0f;
    if (diffuse != 0.0f)
    {
        float specularLight = 0.50f;
        vec3 viewDirection = normalize(cameraPos - pos);
        vec3 halfwayVec = normalize(viewDirection + lightDirection);
        float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
        specular = specAmount * specularLight;
    }

    FragColor = texture(diffuseMap, texUV) * lightColor * (diffuse * diffuseIntensity + ambient + specular);
}
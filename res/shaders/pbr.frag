#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec3 normal;
in vec3 color;
in vec2 texUV;

uniform sampler2D diffuseMap;

uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 lightVec = lightPos - pos;
    float dist = length(lightVec);
    float quadraticTerm = 3.0f;
    float linearTerm = 0.7f;
    float lightIntensity = 1.0f;// / (quadraticTerm * dist * dist + linearTerm * dist + 1.0f);
    
    // ambient lighting
    float ambient = 0.20f;

    // diffuse lighting
    vec3 normal = normalize(normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    FragColor = texture(diffuseMap, texUV) * lightColor * diffuse;
}
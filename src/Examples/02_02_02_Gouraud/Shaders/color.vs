#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 Texcoord;
out float ambient;
out float diff;
out float spec;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 lightColor;
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform float ambientStrength;
uniform int shininess;
uniform sampler2D tex;

void main()
{
	vec3 FragPos = vec3(model * vec4(aPos, 1.0));
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vec3 Normal = mat3(transpose(inverse(model))) * aNormal;

    ambient = ambientStrength;
	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); 
    diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    Texcoord = aTexCoord;
}

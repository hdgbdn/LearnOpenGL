#version 330 core

in vec2 Texcoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;
uniform vec4 lightColor;
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform float ambientStrenth;
uniform int shininess;
uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, Texcoord);
    vec3 norm = normalize(Normal);

    vec3 lightDir = normalize(lightPos - FragPos); 
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    FragColor = (ambientStrenth + diff + spec) * texColor;
}

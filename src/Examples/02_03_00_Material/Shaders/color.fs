#version 330 core

in vec2 Texcoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;
uniform vec3 viewPos; 
uniform sampler2D tex;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;
uniform Light light;

void main()
{
    vec4 texColor = texture(tex, Texcoord);
    vec3 norm = normalize(Normal);

    vec3 ambient = material.ambient * light.ambient;

    vec3 lightDir = normalize(light.position - FragPos); 
    vec3 diffuse  = max(dot(norm, lightDir), 0.0) * material.diffuse * light.diffuse; 

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (spec * material.specular) * light.specular; 

    FragColor = vec4(ambient + diffuse + specular, 1.0) * texColor;
}

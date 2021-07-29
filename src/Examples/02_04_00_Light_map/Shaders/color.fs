#version 330 core

in vec2 Texcoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;
uniform vec3 viewPos; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
}; 
  
uniform Material material;
uniform Light light;

void main()
{
    vec3 texDiffCol = (texture(material.diffuse, Texcoord)).rgb;
    vec3 texSpecCol = (texture(material.specular, Texcoord)).rgb;
    vec3 norm = normalize(Normal);

    vec3 ambient = texDiffCol * light.ambient;

    vec3 lightDir = normalize(light.position - FragPos); 
    vec3 diffuse  = max(dot(norm, lightDir), 0.0) * texDiffCol * light.diffuse; 

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * texSpecCol * light.specular; 

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}

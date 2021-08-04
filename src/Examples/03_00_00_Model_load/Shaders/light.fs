#version 330 core

in vec2 Texcoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;
uniform vec3 viewPos; 

struct DirectionalLight {
    vec3 direction;

    float ambient;
    float diffuse;
    float specular;
};

struct PointLight {
    vec3 position;  
  
    float ambient;
    float diffuse;
    float specular;
	
    float constant;
    float linear;
    float quadratic;
}; 

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
    sampler2D texture_normal1;
    sampler2D texture_height2;
    float     shininess;
}; 
  
uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight pointLight;

#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse1, Texcoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, Texcoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, Texcoord));
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse1, Texcoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, Texcoord));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, Texcoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    //for(int i = 0; i < NR_POINT_LIGHTS; i++)
        //result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    

    FragColor = vec4(result, 1.0);
}

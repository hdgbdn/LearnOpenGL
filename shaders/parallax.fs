#version 330 core
out vec4 FragColor;

in GS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 tanLightPos;
    vec3 tanViewPos;
    vec3 tanFragPos;
    vec3 lightPos;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;
uniform sampler2D texture_specular1;
uniform samplerCube shadowMap;

uniform float far_plane;
uniform float height_scale;

float ShadowCalculation(vec3 fragPos)
{
    vec3 fragToLight = fragPos - fs_in.lightPos;
    float closestDepth = texture(shadowMap, fragToLight).r;
    closestDepth *= far_plane;
    float currentDepth = length(fragToLight);
    
    float bias = 0.05; 
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    shadow = 0.0;
    return shadow;
}


vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{

    const float numLayers = 10;
    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    vec2 P = viewDir.xy * height_scale; 
    vec2 deltaTexCoords = P / numLayers;

    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(texture_height1, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(texture_height1, currentTexCoords).r;
        currentLayerDepth += layerDepth;  
    }

    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;
    float preDepthMapValue = texture(texture_height1, prevTexCoords).r;
    float preLayerDepth = currentLayerDepth - layerDepth;

    float afterDepth = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = preDepthMapValue - preLayerDepth;

    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

void main()
{
    vec3 viewDir = normalize(fs_in.tanViewPos - fs_in.tanFragPos);
    vec2 texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);
    vec3 color = texture(texture_diffuse1, texCoords).rgb;
    vec3 normal = normalize(texture(texture_normal1, texCoords).rgb);
    vec3 lightColor = vec3(1.0);
    // ambient
    vec3 ambient = 0.3 * color;
    // diffuse
    vec3 lightDir = normalize(fs_in.tanLightPos - fs_in.tanFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPos);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    FragColor = vec4(lighting, 1.0);
}  
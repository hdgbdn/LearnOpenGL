#version 330 core
out vec4 FragColor;

in vec3 WorldPos;

uniform samplerCube skybox;

void main()
{
    vec3 envColor = textureLod(skybox, WorldPos, 0).rgb; 
    
    
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 
    
    FragColor = vec4(envColor, 1.0);
}


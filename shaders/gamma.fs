#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform sampler2D texture_diffuse1;

void main()
{
    vec3 color = vec3(fs_in.TexCoords.x, fs_in.TexCoords.x, fs_in.TexCoords.x);
    float gamma = 2.2;
    if(gl_FragCoord.y < 500){
        color = pow(color, vec3(1.0/gamma));
    }
    if(gl_FragCoord.y > 800){
        color = pow(color, vec3(gamma));
    }
    FragColor = vec4(color, 1.0);
}


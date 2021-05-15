#version 330 core
out vec4 FragColor;

in VS_OUT
{
    vec2 TexCoords;
} fs_in;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    vec4 texColor = texture(texture_diffuse1, fs_in.TexCoords);
    FragColor = texColor;
    //FragColor = vec4(0.5, 1.0, 1.0, 1.0);
}


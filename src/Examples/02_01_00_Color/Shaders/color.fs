#version 330 core
in vec2 texcoord;

out vec4 FragColor;
uniform vec4 lightColor;
uniform sampler2D tex;
void main()
{
    FragColor = lightColor * texture(tex, texcoord);
}

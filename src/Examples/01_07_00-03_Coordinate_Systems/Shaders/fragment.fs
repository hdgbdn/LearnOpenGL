#version 330 core
out vec4 FragColor;
in vec3 out_color;
in vec2 texcoord;
uniform sampler2D tex_1;
void main()
{
    FragColor = texture(tex_1, texcoord);
}
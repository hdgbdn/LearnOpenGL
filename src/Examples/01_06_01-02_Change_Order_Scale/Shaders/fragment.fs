#version 330 core
out vec4 FragColor;
in vec3 out_color;
in vec2 texcoord;
uniform sampler2D tex_1;
uniform sampler2D tex_2;
uniform float ratio;
void main()
{
    FragColor = mix(texture(tex_1, texcoord), texture(tex_2, vec2(texcoord.x, 1.0 - texcoord.y)), ratio);
}
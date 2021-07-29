#version 330 core

in vec2 Texcoord;
in vec3 Normal;
in float ambient;
in float diff;
in float spec;

out vec4 FragColor;
uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, Texcoord);

    FragColor = (ambient + diff + spec) * texColor;
}

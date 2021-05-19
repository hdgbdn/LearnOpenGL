#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;
uniform vec2 offsets[100];
uniform float time;

out VS_OUT{
    vec2 TexCoords;
} vs_out;

void main()
{
    vs_out.TexCoords = aTexCoords;
    vec2 offset = offsets[gl_InstanceID];
    vec3 offsetPos;
    offsetPos.x = aPos.x + offset.x;
    offsetPos.y = aPos.y + offset.y;
    offsetPos.z = aPos.z + 100 * sin(time+gl_InstanceID);
    gl_Position = projection * view * model * vec4(offsetPos, 1.0);
}


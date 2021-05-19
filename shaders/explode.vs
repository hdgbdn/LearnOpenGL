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

out VS_OUT{
    vec2 TexCoords;
    vec4 ViewNormal;
    vec4 ViewPos;
    vec4 ModelMovedPos;
    vec4 WorldMovedPos;
} vs_out;

void main()
{
    vs_out.TexCoords = aTexCoords;
    vs_out.ViewNormal = transpose(inverse(view * model)) * vec4(aNormal, 0.0);
    vs_out.ViewPos = view * model * vec4(aPos, 1.0);
    vs_out.ModelMovedPos = vec4(aPos, 1.0) + vec4(aNormal * 30, 0.0);
    vs_out.WorldMovedPos = model * vec4(aPos, 1.0) + model * vec4(aNormal * 30, 0.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}


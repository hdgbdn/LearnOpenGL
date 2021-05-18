#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

in VS_OUT{
    vec2 TexCoords;
    vec4 ViewNormal;
    vec4 ViewPos;
    vec4 ModelMovedPos;
} gs_in[];

out GS_OUT
{
    vec2 TexCoords;
} gs_out;

const float MAGNITUDE = 4;

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    //gl_Position = projection * (gs_in[index].ViewPos + gs_in[index].ViewNormal * MAGNITUDE);
    //gl_Position.w = gl_in[index].gl_Position.w;
    gl_Position = projection * view * model * gs_in[index].ModelMovedPos;
    EmitVertex();
    EndPrimitive();
}

void main() {
    GenerateLine(0);
    gs_out.TexCoords = gs_in[0].TexCoords;
    GenerateLine(1);
    gs_out.TexCoords = gs_in[1].TexCoords;
    GenerateLine(2);
    gs_out.TexCoords = gs_in[2].TexCoords;
}
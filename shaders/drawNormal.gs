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
} gs_in[];

out GS_OUT
{
    vec2 TexCoords;
} gs_out;

const float MAGNITUDE = 0.004;

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = projection * (gs_in[index].ViewPos + gs_in[index].ViewNormal * MAGNITUDE);
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
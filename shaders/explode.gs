#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

in VS_OUT{
    vec2 TexCoords;
    vec3 Normal;
} gs_in[];

out GS_OUT
{
    vec2 TexCoords;
} gs_out;

uniform float time;
uniform mat4 model;

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; 
    return position + vec4(direction, 0.0);
} 

void main() {
    gl_Position = explode(gl_in[0].gl_Position, mat3(projection) * gs_in[0].Normal);
    gs_out.TexCoords = gs_in[0].TexCoords;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, mat3(projection) * gs_in[1].Normal);
    gs_out.TexCoords = gs_in[1].TexCoords;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, mat3(projection) * gs_in[2].Normal);
    gs_out.TexCoords = gs_in[2].TexCoords;
    EmitVertex();
    EndPrimitive();
}
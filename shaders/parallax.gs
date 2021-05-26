#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

out mat4 WorldToTangent;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;
uniform vec3 lightPos;
uniform vec3 viewPos;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} gs_in[];

out GS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 tanLightPos;
    vec3 tanViewPos;
    vec3 tanFragPos;
    vec3 lightPos;
} gs_out;

mat3 CalculateTBN(vec3 normal)
{
    mat3 TBN;
    vec3 A = gs_in[0].FragPos;
    vec3 B = gs_in[1].FragPos;
    vec3 C = gs_in[2].FragPos;

    vec2 A1 = gs_in[0].TexCoords;
    vec2 B1 = gs_in[1].TexCoords;
    vec2 C1 = gs_in[2].TexCoords;

    vec3 edge1 = B - A;
    vec3 edge2 = C - A;
    vec2 deltaUV1 = B1 - A1;
    vec2 deltaUV2 = C1 - A1;
    
    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    TBN[0].x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    TBN[0].y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    TBN[0].z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    
    TBN[1].x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    TBN[1].y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    TBN[1].z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

    TBN[2] = normal;
    return transpose(TBN);
}

void main()
{
    mat3 TBN;   // world to tangent

    gl_Position = gl_in[0].gl_Position; 
    gs_out.FragPos = gs_in[0].FragPos;
    gs_out.Normal = gs_in[0].Normal;
    gs_out.TexCoords = gs_in[0].TexCoords;
    TBN = CalculateTBN(gs_in[0].Normal);
    gs_out.tanLightPos = TBN * lightPos;
    gs_out.tanViewPos = TBN * viewPos;
    gs_out.tanFragPos = TBN * gs_in[0].FragPos;
    gs_out.lightPos = lightPos;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    gs_out.FragPos = gs_in[1].FragPos;
    gs_out.Normal = gs_in[1].Normal;
    gs_out.TexCoords = gs_in[1].TexCoords;
    TBN = CalculateTBN(gs_in[1].Normal);
    gs_out.tanLightPos = TBN * lightPos;
    gs_out.tanViewPos = TBN * viewPos;
    gs_out.tanFragPos = TBN * gs_in[1].FragPos;
    gs_out.lightPos = lightPos;
    EmitVertex();
     
    gl_Position = gl_in[2].gl_Position;
    gs_out.FragPos = gs_in[2].FragPos;
    gs_out.Normal = gs_in[2].Normal;
    gs_out.TexCoords = gs_in[2].TexCoords;
    TBN = CalculateTBN(gs_in[2].Normal);
    gs_out.tanLightPos = TBN * lightPos;
    gs_out.tanViewPos = TBN * viewPos;
    gs_out.tanFragPos = TBN * gs_in[2].FragPos;
    gs_out.lightPos = lightPos;
    EmitVertex();
    
    EndPrimitive();
} 
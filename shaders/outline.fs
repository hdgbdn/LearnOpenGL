#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    //FragColor = vec4(vec3(gl_FragCoord.z/gl_FragCoord.w), 1.0);
    FragColor = vec4(0.5, 1.0, 1.0, 1.0);
}
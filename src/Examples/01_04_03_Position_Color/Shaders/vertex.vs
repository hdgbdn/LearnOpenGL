#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 out_color;

uniform vec3 offset;

void main()
{
   vec3 final_pos = aPos + offset;
   gl_Position = vec4(aPos + offset, 1.0);
   out_color = final_pos;
}
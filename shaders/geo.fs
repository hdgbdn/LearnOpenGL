#version 330 core
out vec4 FragColor;
in vec3 fColor;  
in VS_OUT {
    vec3 color;
} fs_in;
void main()
{
    FragColor = vec4(fColor, 1.0);
    //FragColor = vec4(fs_in.color, 1.0);
}


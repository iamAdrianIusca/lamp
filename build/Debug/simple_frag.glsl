#version 430 core

out vec4 color;

layout (location = 3) uniform vec3 u_color;

void main()
{
   color = vec4(u_color, 1.0f);
}
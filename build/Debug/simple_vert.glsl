#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 projection;
layout (location = 2) uniform mat4 view;

layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);

    out_position = vec3(model * vec4(position, 1.0));
    out_normal   = normal;
}
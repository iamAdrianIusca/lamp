#version 430 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

layout (location = 0) uniform mat4 u_model;

layout (std140, binding = 0) uniform camera
{
    mat4 projection;
    mat4 view;
} u_camera;

layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;

void main()
{
    gl_Position = u_camera.projection * u_camera.view * u_model * vec4(in_position, 1.0);

    out_position = vec3(u_model * vec4(in_position, 1.0));
    out_normal   = in_normal;
}
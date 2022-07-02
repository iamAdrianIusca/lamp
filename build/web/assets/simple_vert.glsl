#version 300 es
precision highp float;

in vec3 in_position;
in vec3 in_normal;

uniform mat4 u_model;

uniform camera
{
    mat4 projection;
    mat4 view;
} u_camera;

out vec3 out_position;
out vec3 out_normal;

void main()
{
    gl_Position = u_camera.projection * u_camera.view * u_model * vec4(in_position, 1.0);

    out_position = vec3(u_model * vec4(in_position, 1.0));
    out_normal   = in_normal;
}
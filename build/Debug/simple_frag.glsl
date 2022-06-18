#version 430 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

layout (location = 3) uniform vec3 u_color;
layout (location = 4) uniform vec3 u_light_color;
layout (location = 5) uniform vec3 u_light_position;

layout (location = 0) out vec4 out_color;

void main()
{
    float ambientStrength = 0.2;
    vec3  ambient = ambientStrength * u_light_color;

    vec3 normal = normalize(in_normal);
    vec3 direction = normalize(u_light_position - in_position);

    float diff = max(dot(normal, direction), 0.0);
    vec3 diffuse = diff * u_light_color;

    vec3 color = (ambient + diffuse) * u_color;
    out_color  = vec4(color, 1.0f);
}
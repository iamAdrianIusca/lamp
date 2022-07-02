#version 300 es
precision highp float;

in vec3 out_position;
in vec3 out_normal;

uniform vec3 u_color;

uniform light
{
    vec3 position;
    float tmp;
    vec3 color;
} u_light;

layout (location = 0) out vec4 out_color;

void main()
{
    // ambient
    float ambientStrength = 0.3;
    vec3  ambient = ambientStrength * u_light.color;

    // diffuse
    vec3 normal    = normalize(out_normal);
    vec3 direction = normalize(u_light.position - out_position);

    float diff   = max(dot(normal, direction), 0.0);
    vec3 diffuse = diff * u_light.color;

    // result
    vec3 color = (ambient + diffuse) * u_color;
    out_color  = vec4(color, 1.0f);
}
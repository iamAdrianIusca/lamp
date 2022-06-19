#pragma once

#include "vec3.hpp"
#include "rgb.hpp"

struct light
{
    vec3 position;
    float tmp;
    rgb  color;
};
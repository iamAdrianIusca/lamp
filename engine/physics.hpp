#pragma once

#include "ray.hpp"
#include "camera.hpp"

#include <btBulletCollisionCommon.h>

class Physics
{
public:
    static ray screen_to_world(const glm::vec2& mouse, const data::camera& camera, const glm::vec4& viewport);
    static btCollisionWorld::ClosestRayResultCallback ray_cast(btCollisionWorld* world, const ray& ray, float distance);
};
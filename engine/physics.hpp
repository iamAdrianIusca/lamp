#pragma once

#include "ray.hpp"
#include "camera.hpp"

#include <btBulletCollisionCommon.h>

class Physics
{
public:
    Physics();

    void init();
    void release();

    static ray screen_to_world(const glm::vec2& mouse, const data::camera& camera, const glm::vec4& viewport);

    btCollisionWorld::ClosestRayResultCallback ray_cast(const ray& ray, float distance) const;

    void add_collision_object(btCollisionShape* shape, const glm::vec3& position);

private:
    btCollisionConfiguration*  _config;
    btCollisionDispatcher* _dispatcher;
    btBroadphaseInterface* _broadphase;
    btCollisionWorld*      _world;
};
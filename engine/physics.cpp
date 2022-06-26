#include "physics.hpp"

#include <glm/gtc/matrix_transform.hpp>

ray Physics::screen_to_world(const glm::vec2 &mouse, const data::camera& camera, const glm::vec4 &viewport)
{
    glm::vec3 start     = glm::unProject(glm::vec3(mouse.x, mouse.y, 0.0f), camera.view, camera.projection, viewport);
    glm::vec3 end       = glm::unProject(glm::vec3(mouse.x, mouse.y, 1.0f), camera.view, camera.projection, viewport);
    glm::vec3 direction = glm::normalize(end - start);

    return { start, direction };
}

btCollisionWorld::ClosestRayResultCallback Physics::ray_cast(btCollisionWorld *world, const ray &ray, const float distance)
{
    btVector3 origin(ray.origin.x, ray.origin.y, ray.origin.z);
    btVector3 direction(ray.direction.x, ray.direction.y, ray.direction.z);

    btVector3 target = origin + direction * distance;

    btCollisionWorld::ClosestRayResultCallback hit(origin, target);
    world->rayTest(origin, target, hit);

    return hit;
}

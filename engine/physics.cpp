#include "physics.hpp"

Physics::Physics()
    : _world { nullptr }
{
}

void Physics::init()
{
    _config     = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_config);
    _broadphase = new btDbvtBroadphase();

    _world = new btCollisionWorld(_dispatcher, _broadphase, _config);
}

void Physics::release()
{
    delete _world;

    delete _broadphase;
    delete _dispatcher;
    delete _config;
}

ray Physics::screen_to_world(const glm::vec2 &mouse, const data::camera& camera, const glm::vec4 &viewport)
{
    glm::vec3 start     = glm::unProject(glm::vec3(mouse.x, mouse.y, 0.0f), camera.view, camera.projection, viewport);
    glm::vec3 end       = glm::unProject(glm::vec3(mouse.x, mouse.y, 1.0f), camera.view, camera.projection, viewport);
    glm::vec3 direction = glm::normalize(end - start);

    return { start, direction };
}

btCollisionWorld::ClosestRayResultCallback Physics::ray_cast(const ray &ray, const float distance) const
{
    btVector3 origin(ray.origin.x, ray.origin.y, ray.origin.z);
    btVector3 direction(ray.direction.x, ray.direction.y, ray.direction.z);

    btVector3 target = origin + direction * distance;

    btCollisionWorld::ClosestRayResultCallback hit(origin, target);
    _world->rayTest(origin, target, hit);

    return hit;
}

void Physics::add_collision_object(btCollisionShape* shape, const glm::vec3& position)
{
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin({ position.x, position.y, position.z });

    auto object = new btCollisionObject();

    object->setCollisionShape(shape);
    object->setWorldTransform(transform);

    _world->addCollisionObject(object);
}

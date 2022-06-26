#include <glad/glad.h>

#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"
#include "buffer.hpp"
#include "keys.hpp"
#include "time.hpp"
#include "file.hpp"
#include "importer.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "physics.hpp"

#define LOAD_SINGLE_VBO  true
#define LOAD_SINGLE_MESH false

int main()
{
    const int width  = 1000;
    const int height = 1000;

    Window window;
    window.create("Game Engine", width, height);

    Shader shader(File::read_file("simple_vert.glsl").c_str(),
                  File::read_file("simple_frag.glsl").c_str());

    std::vector<model> models = Importer::import("tic_tac_toe.obj");

    #if LOAD_SINGLE_VBO

    model merged = model::merge(models, LOAD_SINGLE_MESH);

    VertexArray merged_vao;
    merged_vao.init();
    merged_vao.bind();

    Buffer merged_vbo(GL_ARRAY_BUFFER,         GL_STATIC_DRAW, merged.vertices.size() * sizeof(vertex),  merged.vertices.data());
    Buffer merged_ibo(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, merged.indices.size() * sizeof(uint32_t), merged.indices.data());

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    Mesh merged_mesh(GL_TRIANGLES);
    merged_mesh.vao       = &merged_vao;
    merged_mesh.submeshes = merged.submeshes;

    #else

    model x_model     = models[0];
    model o_model     = models[1];
    model frame_model = models[2];

    VertexArray o_vao;
    o_vao.init();
    o_vao.bind();

    // create vbo buffer for vertices
    Buffer o_vboBuffer(GL_ARRAY_BUFFER,         GL_STATIC_DRAW, o_model.vertices.size() * sizeof(vertex),      o_model.vertices.data());
    Buffer o_iboBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, o_model.indices.size() * sizeof(unsigned int), o_model.indices.data());

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    Mesh o_mesh;
    o_mesh.vao       = &o_vao;
    o_mesh.submeshes = o_model.submeshes;

    VertexArray x_vao;
    x_vao.init();
    x_vao.bind();

    // create vbo buffer for vertices
    Buffer x_vboBuffer(GL_ARRAY_BUFFER,         GL_STATIC_DRAW, x_model.vertices.size() * sizeof(vertex),      x_model.vertices.data());
    Buffer x_iboBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, x_model.indices.size() * sizeof(unsigned int), x_model.indices.data());

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    Mesh x_mesh;
    x_mesh.vao       = &x_vao;
    x_mesh.submeshes = x_model.submeshes;

    VertexArray frame_vao;
    frame_vao.init();
    frame_vao.bind();

    // create vbo buffer for vertices
    Buffer frame_vboBuffer(GL_ARRAY_BUFFER,         GL_STATIC_DRAW, frame_model.vertices.size() * sizeof(vertex),      frame_model.vertices.data());
    Buffer frame_iboBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, frame_model.indices.size() * sizeof(unsigned int), frame_model.indices.data());

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    Mesh frame_mesh;
    frame_mesh.vao       = &frame_vao;
    frame_mesh.submeshes = frame_model.submeshes;

    #endif

    light  light { { 0.0f, 0.0f, 8.0f }, 1.0f, { 1.0f, 1.0f, 1.0f } };

    Buffer light_ubo(GL_UNIFORM_BUFFER, GL_STATIC_DRAW, sizeof(light), &light);
    light_ubo.bind(1);

    data::camera camera;
    camera.projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    camera.view       = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -31.0f));

    Buffer camera_ubo(GL_UNIFORM_BUFFER, GL_STATIC_DRAW, sizeof(camera), &camera);
    camera_ubo.bind(0);

    // initialize delta time
    float lastFrame = 0.0f;

    glEnable(GL_DEPTH_TEST);

    auto bt_config     = new btDefaultCollisionConfiguration();
    auto bt_dispatcher = new btCollisionDispatcher(bt_config);
    auto bt_broadphase = new btDbvtBroadphase();

    auto bt_world = new btCollisionWorld(bt_dispatcher, bt_broadphase, bt_config);

    btTransform bt_transform;
    bt_transform.setIdentity();

    auto bt_box   = new btCollisionObject();
    auto bt_shape = new btBoxShape(btVector3(2.80f, 2.80f, 1.0f));

    bt_box->setCollisionShape(bt_shape);
    bt_box->setWorldTransform(bt_transform);
    bt_world->addCollisionObject(bt_box);

    glm::vec4 viewport { 0.0f, 0.0f, width, height };

    // show the window
    while (!window.isClosed())
    {
        bool yellow = false;

        if (window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            glm::vec2 mouse = window.mouse_position();

            auto ray = Physics::screen_to_world(mouse, camera, viewport);
            auto hit = Physics::ray_cast(bt_world, ray, 50.0f);

            if (hit.hasHit())
            {
                yellow = true;
            }
        }

        // calculate delta time
        auto currentFrame = Time::getTotalTime();
        float deltaTime   = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // close the window on escape key
        if (window.isKeyPressed(ESC_KEY))
        {
            window.close();
        }

        window.clear();

        shader.use();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::vec3 color     = glm::vec3(1.0f, 0.0f, 0.0f);

        if (yellow)
        {
            color = glm::vec3(1.0f, 1.0f, 0.0f);
        }

        shader.setMat4(0, glm::value_ptr(transform));
        shader.setVec3(1, glm::value_ptr(color));

        #if LOAD_SINGLE_VBO

        merged_mesh.bind();
        merged_mesh.draw(1);

        #else

        o_mesh.bind();
        o_mesh.draw(0);

        #endif

        transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        color     = glm::vec3(0.0f, 1.0f, 0.0f);

        shader.setMat4(0, glm::value_ptr(transform));
        shader.setVec3(1, glm::value_ptr(color));

        #if  LOAD_SINGLE_VBO
        #if !LOAD_SINGLE_MESH

        merged_mesh.draw(0);

        #endif
        #else

        x_mesh.bind();
        x_mesh.draw(0);

        #endif

        transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        color     = glm::vec3(0.0f, 0.0f, 1.0f);

        shader.setMat4(0, glm::value_ptr(transform));
        shader.setVec3(1, glm::value_ptr(color));

        #if  LOAD_SINGLE_VBO
        #if !LOAD_SINGLE_MESH

        merged_mesh.draw(2);

        #endif
        #else

        frame_mesh.bind();
        frame_mesh.draw(0);

        #endif

        window.update();
    }

    window.destroy();

    return 0;
}

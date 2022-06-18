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
#include "mesh.hpp"

int main()
{
    const int width  = 1200;
    const int height = 1200;

    Window window;
    window.create("Game Engine", width, height);

    Shader shader(File::read_file("simple_vert.glsl").c_str(),
                  File::read_file("simple_frag.glsl").c_str());

    std::vector<model> models = Importer::import("tic_tac_toe.obj");

    model x_model     = models[0];
    model o_model     = models[1];
    model frame_model = models[2];

    VertexArray o_vao;
    o_vao.bind();

    // create vbo buffer for vertices
    Buffer o_vboBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, o_model.vertices.size() * sizeof(vertex), o_model.vertices.data());
    Buffer o_iboBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, o_model.indices.size() * sizeof(unsigned int), o_model.indices.data());

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    Mesh o_mesh;
    o_mesh.vao = o_vao;
    o_mesh.submeshes.push_back({ 0, (unsigned int)o_model.indices.size() });

    VertexArray x_vao;
    x_vao.bind();

    // create vbo buffer for vertices
    Buffer x_vboBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, x_model.vertices.size() * sizeof(vertex), x_model.vertices.data());
    Buffer x_iboBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, x_model.indices.size() * sizeof(unsigned int), x_model.indices.data());

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    VertexArray frame_vao;
    frame_vao.bind();

    // create vbo buffer for vertices
    Buffer frame_vboBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, frame_model.vertices.size() * sizeof(vertex), frame_model.vertices.data());
    Buffer frame_iboBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, frame_model.indices.size() * sizeof(unsigned int), frame_model.indices.data());

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // initialize delta time
    float lastFrame = 0.0f;

    glEnable(GL_DEPTH_TEST);

    // show the window
    while (!window.isClosed())
    {
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

        // calculate perspective matrix with glm
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -31.0f));

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        shader.setMat4(0, glm::value_ptr(transform));
        shader.setMat4(1, glm::value_ptr(proj));
        shader.setMat4(2, glm::value_ptr(view));

        o_mesh.bind();
        o_mesh.draw(0);

        transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        shader.setMat4(0, glm::value_ptr(transform));

        x_vao.bind();
        glDrawElements(GL_TRIANGLES, x_model.indices.size(), GL_UNSIGNED_INT, 0);

        transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        shader.setMat4(0, glm::value_ptr(transform));

        frame_vao.bind();
        glDrawElements(GL_TRIANGLES, frame_model.indices.size(), GL_UNSIGNED_INT, 0);

        window.update();
    }

    window.destroy();

    return 0;
}

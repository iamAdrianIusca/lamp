#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window.hpp"
#include "shader.hpp"

int main()
{
    // declare window size
    const int width  = 800;
    const int height = 600;

    Window window;
    window.create("Game Engine", width, height);

    // create vertex shader source code
    const char* vertexShaderSource = "#version 430 core\n"
                                     "layout (location = 0) in vec3 position;\n"
                                     "layout (location = 0) uniform mat4 model;\n"
                                     "layout (location = 1) uniform mat4 projection;\n"
                                     "layout (location = 2) uniform mat4 view;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = projection * view * model * vec4(position, 1.0);\n"
                                     "}\0";

    // create fragment shader source code
    const char* fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 color;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    Shader shader(vertexShaderSource, fragmentShaderSource);

    // create a vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // create vertex buffer object data
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // initialize delta time
    float lastFrame = 0.0f;

    glEnable(GL_DEPTH_TEST);

    // show the window
    while (!window.isClosed())
    {
        // calculate delta time
        auto currentFrame = (float)glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // rotate glm matrix with delta time
        glm::mat4 rotate    = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 scale     = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

        // calculate perspective matrix with glm
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

        // close the window on escape key
        if (window.isKeyPressed(GLFW_KEY_ESCAPE))
        {
            window.close();
        }

        window.clear();

        shader.use();

        glm::mat4 transform = translate * rotate * scale;

        shader.setMat4(0, glm::value_ptr(transform));
        shader.setMat4(1, glm::value_ptr(proj));
        shader.setMat4(2, glm::value_ptr(view));

        glBindVertexArray(VAO);

        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.update();
    }

    window.destroy();

    return 0;
}
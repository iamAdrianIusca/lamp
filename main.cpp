#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"
#include "shader.hpp"

int main()
{
    // use the Window class

    Window window;
    window.create("Game Engine", 800, 600);

    // create vertex shader source code
    const char* vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 position;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
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

    // show the window
    while (!window.isClosed())
    {
        // close the window on escape key
        if (window.isKeyPressed(GLFW_KEY_ESCAPE))
        {
            window.close();
        }

        window.clear();

        // use shader program
        shader.use();

        // bind vertex array object
        glBindVertexArray(VAO);

        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.update();
    }

    window.destroy();

    return 0;
}
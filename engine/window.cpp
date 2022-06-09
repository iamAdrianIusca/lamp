#include "window.hpp"

#include <iostream>

Window::Window()
{
    m_data.title = "GLFW Window";
    m_data.width = 800;
    m_data.height = 600;
    m_data.isClosed = false;
}

Window::~Window()
{
    destroy();
}

void Window::create(const char *title, int width, int height)
{
    m_data.title = title;
    m_data.width = width;
    m_data.height = height;

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_data.window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    if (!m_data.window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_data.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, m_data.width, m_data.height);
}

void Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_data.window);
}

void Window::clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::destroy()
{
    glfwDestroyWindow(m_data.window);
    glfwTerminate();
}

bool Window::isClosed()
{
    return m_data.isClosed || glfwWindowShouldClose(m_data.window);
}

bool Window::isKeyPressed(unsigned int keycode)
{
    return glfwGetKey(m_data.window, keycode) == GLFW_PRESS;
}

void Window::close()
{
    m_data.isClosed = true;
}

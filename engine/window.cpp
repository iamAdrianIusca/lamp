#include "window.hpp"

Window::Window()
{
    m_data.isClosed = false;
}

void Window::create(const char *title, int width, int height)
{
    m_data.title  = title;
    m_data.width  = width;
    m_data.height = height;

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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

    #ifdef LAMP_WIN32

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    #endif

    #ifdef LAMP_WEB

    glewInit();

    #endif

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::destroy()
{
    glfwDestroyWindow(m_data.window);
    glfwTerminate();
}

bool Window::isClosed() const
{
    return m_data.isClosed || glfwWindowShouldClose(m_data.window);
}

bool Window::isKeyPressed(int keycode) const
{
    return glfwGetKey(m_data.window, keycode) == GLFW_PRESS;
}

void Window::close()
{
    m_data.isClosed = true;
}

bool Window::isMousePressed(int button) const
{
    return glfwGetMouseButton(m_data.window, button) == GLFW_PRESS;
}

glm::vec2 Window::mouse_position() const
{
    double x, y;
    glfwGetCursorPos(m_data.window, &x, &y);

    return { x, y };
}

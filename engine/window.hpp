#pragma once

#include <string>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Window
{
public:
    Window();
    ~Window();

    void create(const char* title, int width, int height);
    void update();
    void clear();
    void destroy();
    void close();

    bool isClosed();
    bool isKeyPressed(unsigned int keycode);

    inline int getWidth() const { return m_data.width; }
    inline int getHeight() const { return m_data.height; }

private:
    struct WindowData
    {
        std::string title;
        int width, height;
        bool isClosed;
        GLFWwindow* window;
    };

    WindowData m_data;
};
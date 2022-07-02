#pragma once

class Window
{
public:
    Window();
    ~Window() = default;

    void create(const char* title, int width, int height);
    void update();
    void clear();
    void destroy();
    void close();

    bool isClosed() const;
    bool isKeyPressed(int keycode)  const;
    bool isMousePressed(int button) const;

    glm::vec2 mouse_position() const;

    int getWidth() const  { return m_data.width;  }
    int getHeight() const { return m_data.height; }

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
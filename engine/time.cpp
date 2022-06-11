#include "time.hpp"

#include <GLFW/glfw3.h>

float Time::getTotalTime()
{
    return (float)glfwGetTime();
}

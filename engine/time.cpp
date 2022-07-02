#include "time.hpp"

float Time::getTotalTime()
{
    return (float)glfwGetTime();
}

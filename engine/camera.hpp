#pragma once

#include <glm/glm.hpp>

namespace data
{
    struct camera
    {
        glm::mat4 projection;
        glm::mat4 view;
    };
}

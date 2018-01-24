#pragma once
#include "glm/glm.hpp"

namespace ren
{
    class DirectionalLight
    {
    private:
        glm::vec3 m_position;
        glm::vec3 m_color;
    public:
        DirectionalLight(glm::vec3 position, glm::vec3 color);
        auto getPosition() const -> const decltype(m_position)&;
        auto getColor() const -> const decltype(m_color)&;
    };
}
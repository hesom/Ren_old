#include "graphics/directionallight.h"

namespace ren
{
    DirectionalLight::DirectionalLight(const glm::vec3 position, const glm::vec3 color) :
        m_position(position),
        m_color(color)
    {

    }
    auto DirectionalLight::getPosition() const -> const decltype(m_position)&
    {
        return m_position;
    }
    auto DirectionalLight::getColor() const -> const decltype(m_color)&
    {
        return m_color;
    }
}
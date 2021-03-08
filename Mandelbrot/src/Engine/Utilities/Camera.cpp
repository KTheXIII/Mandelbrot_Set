#include "Camera.hpp"

namespace EN {

    Camera::Camera()
        : m_Position(1.f),
          m_Front(1.f),
          m_Up(1.f),
          m_View(1.f),
          m_Projection(1.f),
          m_Near(0.01f),
          m_Far(1000.f),
          m_Width(1.f),
          m_Height(1.f) {}

    Camera::~Camera() {}

}  // namespace EN

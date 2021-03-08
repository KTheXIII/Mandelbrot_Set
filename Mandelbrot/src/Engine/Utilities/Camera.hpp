#pragma once

#include "Core/Core.hpp"

#include "Core/Window.hpp"

#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace EN {

    class Camera {
       public:
        Camera();

        ~Camera();

        inline float* GetView() { return glm::value_ptr(m_View); };
        inline float* GetProjection() { return glm::value_ptr(m_Projection); }

       private:
        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_Up;

        glm::mat4 m_View;
        glm::mat4 m_Projection;

        float m_Near;
        float m_Far;

       private:
        int32_t m_Width;
        int32_t m_Height;
    };

}  // namespace EN

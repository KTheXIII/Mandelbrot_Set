#pragma once

#include "Core.hpp"

#include "GLFW/glfw3.h"

namespace EN {
    /**
     * Time keeps track of the time since the application started and the delta
     * time between frames.
     */
    class Time {
       public:
        Time();
        ~Time();

        /**
         * Calls every frame
         */
        inline void Update() {
            m_Previous = m_Current;
            m_Current = glfwGetTime();
            m_Elapsed = m_Current - m_Previous;
        }

        /**
         * Get elapsed time in seconds
         *
         * @return Delta time in seconds
         */
        inline double Elapsed() const { return m_Elapsed; }

       private:
        double m_Current;
        double m_Previous;
        double m_Elapsed;
    };

}  // namespace EN

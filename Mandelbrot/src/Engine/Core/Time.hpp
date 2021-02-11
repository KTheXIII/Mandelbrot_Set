#pragma once

#include "Core.hpp"

namespace EN {
    using time_point = std::chrono::steady_clock::time_point;

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
            m_Current = std::chrono::high_resolution_clock::now();
            m_Elapsed = m_Current - m_Previous;
        }

        /**
         * Get elapsed time in seconds
         *
         * @return Delta time in seconds
         */
        inline double Elapsed() const { return m_Elapsed.count(); }

       private:
        time_point m_Previous;
        time_point m_Current;
        std::chrono::duration<double> m_Elapsed;
    };

}  // namespace EN

#pragma once

#include "Core/Core.hpp"

namespace EN {

    class RenderingContext {
       public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

       private:
    };

}  // namespace EN

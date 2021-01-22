#pragma once

#include "Core/Core.hpp"

namespace EN {

    // TODO: The renderer context is abstracted away atm.
    //       This might not be needed in this project.

    class RenderingContext {
       public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

       private:
    };

}  // namespace EN

#pragma once

#include "Core.hpp"

#include "Window.hpp"
#include "Content.hpp"

namespace EN {
    class Application {
       public:
        Application();

        virtual ~Application();

        void Run();

        virtual void Update() = 0;

        virtual void Render() = 0;

        inline Window& GetWindow() { return *m_Window; }

       private:
        std::unique_ptr<Window> m_Window;
    };
}  // namespace EN
#pragma once;

#include "Core.hpp"

#include "Window.hpp"

namespace EN {
    class Application {
       public:
        Application();
        virtual ~Application();

        void Run();

        inline Window& GetWindow() { return *m_Window; }

        inline Application& Get() { return *s_Instance; }

       private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

        static Application* s_Instance;
    };
}  // namespace EN

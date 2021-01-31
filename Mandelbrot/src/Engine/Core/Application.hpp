#pragma once

#include "Core.hpp"

#include "Window.hpp"
#include "Content.hpp"

namespace EN {

    class Application {
       public:
        Application();

        virtual ~Application();

        virtual void Init() = 0;

        void Run();

        virtual void Update() = 0;

        virtual void Render() = 0;

        inline Window& GetWindow() { return *m_Window; }

        inline void SetArgs(int argc, char const* argv[]) {
            fs::path exec_path = argv[0];  // Get the launced path
            m_Content.SetPath(exec_path);
        }

       protected:
        Content m_Content;

       private:
        std::unique_ptr<Window> m_Window;
    };

}  // namespace EN
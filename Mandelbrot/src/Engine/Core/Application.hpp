#pragma once

#include "Core.hpp"

#include "Window.hpp"
#include "Content.hpp"
#include "Time.hpp"

namespace EN {

    class Application {
       public:
        Application();

        virtual ~Application();

        /**
         * Call once to set the args value for the application
         *
         * @param[in] argc Argument count from main
         * @param[in] argv Argument array pointer from main
         */
        inline void SetArgs(int argc, char const* argv[]) {
            fs::path exec_path = argv[0];  // Get the launced path
            m_Content.SetPath(exec_path);
        }

        /**
         * Starts the application
         */
        void Start();

        /**
         * Starts the application with arguments passing through
         */
        void Start(int argc, char const* argv[]);

        /**
         * Call before Run to initialize the program
         */
        virtual void Init() = 0;

        /**
         * Starts the main loop
         */
        inline void Run();

        /**
         * Calls every frame
         */
        virtual void Update(Time const& time) = 0;

        /**
         * Calls every frame
         */
        virtual void Render() = 0;

        /**
         * Get the Window object
         *
         * @return Application's window instance
         */
        inline Window& GetWindow() { return *m_Window; }

       protected:
        Content m_Content;

       private:
        Time m_Time;
        std::unique_ptr<Window> m_Window;
    };

}  // namespace EN
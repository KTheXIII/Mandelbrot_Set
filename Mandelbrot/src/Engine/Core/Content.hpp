#pragma once

#include "Core.hpp"

namespace EN {
    class Content {
       public:
        Content();

        Content(const std::string& root_path);

        ~Content();

        inline void SetPath(const fs::path& path) {
            m_Path = std::string(path.parent_path().string());
        }

        inline std::string GetPath() const { return m_Path; }

       private:
        std::string m_Path;
    };

}  // namespace EN

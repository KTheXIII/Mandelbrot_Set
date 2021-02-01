#pragma once

#include "Core.hpp"

namespace EN {
    class Content {
       public:
        Content();

        ~Content();

        inline void SetPath(const fs::path& path) {
#ifdef ENGINE_RELEASE
            m_Path = std::string(path.parent_path().string());
#endif  // ENGINE_RELEASE
        }

        inline std::string GetPath() const { return m_Path; }

        inline std::string GetAssetPath(const std::string& name) const {
            return m_Path + "/" + m_Name + "/" + name;
        }

       private:
        std::string m_Path;
        std::string m_Name = "asset";
    };

}  // namespace EN

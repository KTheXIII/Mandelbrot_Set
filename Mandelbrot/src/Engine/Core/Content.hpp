#pragma once

#include "Core.hpp"

namespace EN {

    /**
     * Content stores the corrent path to where the asset directory is located.
     */
    class Content {
       public:
        /**
         * Set the content path to the current directory.
         */
        Content();

        ~Content();

        /**
         * Set the path for release, the default is "." (current directory)
         */
        inline void SetPath(const fs::path& path) {
#ifdef ENGINE_RELEASE
            m_AssetPath = std::string(path.parent_path().string()) + "/";
#endif  // ENGINE_RELEASE
        }

        /**
         * Get the path to asset directory
         *
         * @return Absolute path to where the asset directory lives
         */
        inline std::string GetPath() const { return m_AssetPath; }

        /**
         * Get asset absolute path
         */
        inline std::string GetAssetPath(const std::string& name) const {
            return m_AssetPath + m_AssetName + "/" + name;
        }

        /**
         * Set asset directory name
         *
         * @param[in] name c style string
         */
        inline void SetAssetName(char const* name) { m_AssetName = name; }

        /**
         * Set the asset directory name
         *
         * @param[in] name C++ string
         */
        inline void SetAssetName(const std::string& name) {
            SetAssetName(name.c_str());
        }

       private:
        std::string m_AssetPath;
        std::string m_AssetName = "asset";
    };

}  // namespace EN

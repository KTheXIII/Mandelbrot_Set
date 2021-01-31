#include "Content.hpp"

namespace EN {
    Content::Content() : m_Path("") {}

    Content::Content(const std::string& root_path) : m_Path(root_path) {}

    Content::~Content() {}

}  // namespace EN
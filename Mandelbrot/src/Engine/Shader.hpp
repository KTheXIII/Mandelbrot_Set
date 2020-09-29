#pragma once

namespace MSET {

    class Shader {
       public:
        Shader();
        ~Shader();

        void Bind();

        void UnBind();

       private:
        unsigned int m_ProgramID;  // Shader Program Object
    };

}  // namespace MSET

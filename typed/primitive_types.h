#ifndef PRIMITIVE_TYPES_H
#define PRIMITIVE_TYPES_H

#include <GL/glew.h>

namespace ge1 {
    namespace typed {

        template<class Type>
        struct type_info {};

        template<>
        struct type_info<float> {
            static constexpr GLint size = 1;
            static constexpr GLenum type = GL_FLOAT;
        };

        template<>
        struct type_info<signed int> {
            static constexpr GLint size = 1;
            static constexpr GLenum type = GL_INT;
        };

        template<>
        struct type_info<unsigned int> {
            static constexpr GLint size = 1;
            static constexpr GLenum type = GL_UNSIGNED_INT;
        };

        template<>
        struct type_info<signed short> {
            static constexpr GLint size = 1;
            static constexpr GLenum type = GL_SHORT;
        };

        template<>
        struct type_info<unsigned short> {
            static constexpr GLint size = 1;
            static constexpr GLenum type = GL_UNSIGNED_SHORT;
        };

        template<>
        struct type_info<signed char> {
            static constexpr GLint size = 1;
            static constexpr GLenum type = GL_BYTE;
        };

        template<>
        struct type_info<unsigned char> {
            static constexpr GLint size = 1;
            static constexpr GLenum type = GL_UNSIGNED_BYTE;
        };

    }
}

#endif // PRIMITIVE_TYPES_H

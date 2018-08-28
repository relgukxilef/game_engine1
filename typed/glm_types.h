#ifndef GLM_TYPES_H
#define GLM_TYPES_H

#include <glm/glm.hpp>

#include "primitive_types.h"

namespace ge1 {
    namespace typed {

        template<>
        struct type_info<glm::vec2> {
            static constexpr GLint size = 2;
            static constexpr GLenum type = GL_FLOAT;
        };

        template<>
        struct type_info<glm::vec3> {
            static constexpr GLint size = 3;
            static constexpr GLenum type = GL_FLOAT;
        };

        template<>
        struct type_info<glm::vec4> {
            static constexpr GLint size = 4;
            static constexpr GLenum type = GL_FLOAT;
        };

        template<>
        struct type_info<glm::ivec2> {
            static constexpr GLint size = 2;
            static constexpr GLenum type = GL_INT;
        };

        template<>
        struct type_info<glm::ivec3> {
            static constexpr GLint size = 3;
            static constexpr GLenum type = GL_INT;
        };

        template<>
        struct type_info<glm::ivec4> {
            static constexpr GLint size = 4;
            static constexpr GLenum type = GL_INT;
        };

        template<>
        struct type_info<glm::uvec2> {
            static constexpr GLint size = 2;
            static constexpr GLenum type = GL_UNSIGNED_INT;
        };

        template<>
        struct type_info<glm::uvec3> {
            static constexpr GLint size = 3;
            static constexpr GLenum type = GL_UNSIGNED_INT;
        };

        template<>
        struct type_info<glm::uvec4> {
            static constexpr GLint size = 4;
            static constexpr GLenum type = GL_UNSIGNED_INT;
        };

    }
}

#endif // GLM_TYPES_H

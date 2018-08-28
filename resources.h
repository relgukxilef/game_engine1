#ifndef RESOURCES_H
#define RESOURCES_H

#include <GL/glew.h>

namespace ge1 {

    struct unique_vbo {
        unique_vbo();
        ~unique_vbo();

        GLuint get_name() const;

        operator GLuint() const;

    private:
        GLuint name;
    };

    struct unique_vao {
        unique_vao();
        ~unique_vao();

        GLuint get_name() const;

        operator GLuint() const;

    private:
        GLuint name;
    };


    inline unique_vbo::unique_vbo() {
        glGenBuffers(1, &name);
    }

    inline unique_vbo::~unique_vbo() {
        glDeleteBuffers(1, &name);
    }

    inline GLuint unique_vbo::get_name() const {
        return name;
    }

    inline unique_vbo::operator GLuint() const {
        return get_name();
    }

    inline unique_vao::unique_vao() {
        glGenVertexArrays(1, &name);
    }

    inline unique_vao::~unique_vao() {
        glDeleteVertexArrays(1, &name);
    }

    inline GLuint unique_vao::get_name() const {
        return name;
    }

    inline unique_vao::operator GLuint() const {
        return get_name();
    }

}

#endif // RESOURCES_H

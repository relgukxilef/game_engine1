#ifndef DRAW_CALL_H
#define DRAW_CALL_H

#include <GL/glew.h>

#include "renderable.h"
#include "vertex_array.h"

namespace ge1 {

    struct draw_call : public renderable {
        draw_call(
            GLuint vertex_array, GLint first, GLint count,
            GLuint program, GLenum mode
        );

        void render() override;

        GLuint vertex_array;
        GLint first;
        GLint count;
        GLuint program;
        GLenum mode;
    };

}

#endif // DRAW_CALL_H

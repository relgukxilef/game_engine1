#include "draw_call.h"

namespace ge1 {

    draw_call::draw_call(
        GLuint vertex_array, GLint first, GLint count,
        GLuint program, GLenum mode
    ) :
        vertex_array(vertex_array), first(first), count(count),
        program(program), mode(mode)
    {
    }

    void draw_call::render() {
        glUseProgram(program);
        glBindVertexArray(vertex_array);
        glDrawArrays(mode, first, count);
    }

}

#include "vertex_vector.h"

#include <boost/range/adaptor/reversed.hpp>

#include "vertex_buffer.h"
#include "resources.h"

using namespace boost::intrusive;
using namespace boost::adaptors;
using namespace std;

namespace ge1 {

    void delete_vbo(GLuint vbo) {
        glDeleteBuffers(1, &vbo);
    }

    typedef unique_object<delete_vbo> unique_vbo;

    slist<vertex_attribute_pack> concat(
        initializer_list<vertex_attribute_pack_vector*> packs
    ) {
        // TODO: make this a utility function
        slist<vertex_attribute_pack> list;

        for (auto pointer : reverse(packs)) {
            list.push_front(*pointer);
        }

        return list;
    }

    GLuint new_vertex_buffer_object() {
        GLuint name;
        glGenBuffers(1, &name);
        return name;
    }

    GLuint new_vertex_array_object() {
        GLuint name;
        glGenVertexArrays(1, &name);
        return name;
    }


    vertex_attribute_pack_vector::vertex_attribute_pack_vector(
            GLint stride, std::initializer_list<vertex_attribute*> attributes
    ) : vertex_attribute_pack(new_vertex_buffer_object(), stride, attributes) {}

    vertex_attribute_pack_vector::vertex_attribute_pack_vector(
        std::initializer_list<vertex_attribute*> attributes
    ) : vertex_attribute_pack(new_vertex_buffer_object(), attributes) {}

    vertex_attribute_pack_vector::~vertex_attribute_pack_vector() {
        glDeleteBuffers(1, &vbo);
    }

    vertex_vector::vertex_vector(
        std::initializer_list<vertex_attribute_pack_vector*> attribute_packs,
        GLsizei capacity
    ) :
        vertex_array(new_vertex_array_object(), 0, 0, concat(attribute_packs)),
        capacity(capacity)
    {
        for (auto& pack : this->get_attribute_packs()) {
            glBindBuffer(GL_COPY_WRITE_BUFFER, pack.get_vbo());
            glBufferData(
                GL_COPY_WRITE_BUFFER, pack.get_stride() * capacity, nullptr,
                GL_DYNAMIC_DRAW
            );
        }
    }

    ge1::vertex_vector::~vertex_vector() {
        glDeleteVertexArrays(1, &vao);
    }

    void vertex_vector::push_back(vertex_buffer& buffer) {
        if (count + static_cast<GLsizei>(buffer.get_capacity()) > capacity) {
            // This might be slow
            GLsizei new_capacity = max(
                count + static_cast<GLsizei>(buffer.get_capacity()),
                capacity * 2
            );

            for (auto& pack : get_attribute_packs()) {
                unique_vbo temp;
                glBindBuffer(GL_COPY_WRITE_BUFFER, temp.get_name());
                glBufferData(
                    GL_COPY_WRITE_BUFFER, pack.get_stride() * capacity,
                    nullptr,
                    GL_DYNAMIC_DRAW
                );

                glBindBuffer(GL_COPY_READ_BUFFER, pack.get_vbo());
                glCopyBufferSubData(
                    GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0,
                    pack.get_stride() * capacity
                );

                glBufferData(
                    GL_COPY_READ_BUFFER, pack.get_stride() * new_capacity,
                    nullptr,
                    GL_DYNAMIC_DRAW
                );
                glCopyBufferSubData(
                    GL_COPY_WRITE_BUFFER, GL_COPY_READ_BUFFER, 0, 0,
                    pack.get_stride() * capacity
                );
            }
        }

        copy_from(count, buffer);
        count += buffer.get_capacity();
    }

}

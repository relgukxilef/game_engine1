#include "vertex_array.h"

#include <utility>

#include <boost/range/adaptor/reversed.hpp>

#include "vertex_buffer.h"

using namespace boost::intrusive;
using namespace boost::adaptors;
using namespace std;

namespace ge1 {

    slist<vertex_attribute_pack> concat(
        initializer_list<vertex_attribute_pack*> packs
    ) {
        // TODO: make this a utility function
        slist<vertex_attribute_pack> list;

        for (auto pointer : reverse(packs)) {
            list.push_front(*pointer);
        }

        return list;
    }

    int get_size(GLenum type) {
        switch (type) {

        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
            return 1;

        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_HALF_FLOAT:
            return 2;

        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_FLOAT:
            return 4;

        case GL_DOUBLE:
            return 8;

        default:
            return 1;
        }
    }


    vertex_attribute_pack::vertex_attribute_pack(
        GLuint vbo, GLint stride,
        std::initializer_list<vertex_attribute*> attributes
    )  : vbo(vbo), stride(stride) {

        for (
            auto a = attributes.end() - 1;
            a != attributes.begin() - 1;
            a--
        ) {
            auto& attribute = **a;
            this->attributes.push_front(attribute);
            attribute.pack = this;
        }

        GLuint next_index = 0;
        GLsizei next_offset = 0;

        for (auto a : attributes) {
            auto& attribute = *a;
            if (attribute.auto_index) {
                attribute.index = next_index;
            }
            next_index = attribute.index + 1;

            if (attribute.auto_offset) {
                attribute.offset = next_offset;
            }
            next_offset =
                attribute.offset + get_size(attribute.type) * attribute.size;
        }

        if (stride == 0) {
            this->stride = next_offset;
        }
    }

    vertex_attribute_pack::vertex_attribute_pack(
        GLuint vbo, std::initializer_list<vertex_attribute*> attributes
    ) : vertex_attribute_pack(vbo, 0, attributes) {}

    vertex_array_data::vertex_array_data(
        boost::intrusive::slist<vertex_attribute_pack>&& attribute_packs
    ) : attribute_packs(std::move(attribute_packs)) {

        unsigned int next_index = 0;

        for (auto &pack : this->attribute_packs) {
            pack.index = next_index;
            next_index++;
        }
    }

    vertex_array_data::vertex_array_data(
        std::initializer_list<vertex_attribute_pack*> attribute_packs
    ) : vertex_array_data(concat(attribute_packs))
    {}

    void vertex_array_data::copy_from(int first, const vertex_buffer& buffer) {
        for (auto& p : attribute_packs) {
            glBindBuffer(GL_COPY_WRITE_BUFFER, p.vbo);

            glBufferSubData(
                GL_COPY_WRITE_BUFFER,
                first * p.stride,
                buffer.get_capacity() * static_cast<size_t>(p.stride),
                buffer[p].begin()
            );
        }
    }

    void vertex_array_data::copy_to(int first, vertex_buffer& buffer) const {
        ;
    }

    vertex_array::vertex_array(
        GLuint vao, GLint first, GLsizei count,
        boost::intrusive::slist<vertex_attribute_pack>&& attribute_packs
    ) :
        vertex_array_data(std::move(attribute_packs)),
        vao(vao), first(first), count(count)
    {
        glBindVertexArray(vao);
        for (auto& p : get_attribute_packs()) {

            glBindBuffer(GL_ARRAY_BUFFER, p.get_vbo());
            for (auto& a : p.get_attributes()) {

                glEnableVertexAttribArray(a.get_index());
                glVertexAttribPointer(
                    a.get_index(), a.get_size(), a.get_type(),
                    a.get_normalize(), p.get_stride(),
                    reinterpret_cast<void*>(a.get_offset())
                );
            }
        }
    }

    vertex_array::vertex_array(
        GLuint vao, GLint first, GLsizei count,
        std::initializer_list<vertex_attribute_pack*> attribute_packs
    ) : vertex_array(
        vao, first, count, concat(attribute_packs)
    ) {}

}

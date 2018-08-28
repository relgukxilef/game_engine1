#ifndef VERTEX_VECTOR_H
#define VERTEX_VECTOR_H

#include "vertex_array.h"

#include "resources.h"

namespace ge1 {

    struct vertex_attribute_pack_vector : public vertex_attribute_pack {
        friend struct vertex_vector;

        vertex_attribute_pack_vector(
            GLint stride,
            std::initializer_list<vertex_attribute*> attributes
        );
        vertex_attribute_pack_vector(
            std::initializer_list<vertex_attribute*> attributes
        );

        ~vertex_attribute_pack_vector();
    };

    struct vertex_vector : public vertex_array {
        vertex_vector(
            std::initializer_list<vertex_attribute_pack_vector*>
                attribute_packs,
            GLsizei capacity = 256
        );

        ~vertex_vector();

        void push_back(vertex_buffer& buffer);

    private:
        GLsizei capacity;
    };

}

#endif // VERTEX_VECTOR_H

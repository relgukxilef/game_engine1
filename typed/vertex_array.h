#ifndef TYPED_VERTEX_ARRAY_H
#define TYPED_VERTEX_ARRAY_H

#include <GL/glew.h>

#include "../vertex_array.h"
#include "primitive_types.h"

#include "vertex_buffer.h"

namespace ge1 {
    namespace typed {

        template<class Type, int Offset>
        struct vertex_attribute : public ge1::vertex_attribute {

            vertex_attribute(GLuint index, GLboolean normalize);
            vertex_attribute(GLboolean normalize);

            Type& operator()(const ge1::vertex_buffer::reference& vertex);
        };

        template<class Type, int Offset>
        vertex_attribute<Type, Offset>::vertex_attribute(
            GLuint index, GLboolean normalize
        ) : ge1::vertex_attribute(
            index, type_info<Type>::size, type_info<Type>::type,
            normalize, Offset
        ) {}

        template<class Type, int Offset>
        vertex_attribute<Type, Offset>::vertex_attribute(
            GLboolean normalize
        ) : ge1::vertex_attribute(
            type_info<Type>::size, type_info<Type>::type, normalize, Offset
        ) {}

        template<class Type, int Offset>
        Type& vertex_attribute<Type, Offset>::operator()(
            const ge1::vertex_buffer::reference& vertex
        ) {
            return *reinterpret_cast<Type*>(
                vertex[*get_pack()].get_data() + Offset
            );
        }

    }
}

#endif // TYPED_VERTEX_ARRAY_H

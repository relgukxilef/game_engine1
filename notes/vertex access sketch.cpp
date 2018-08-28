#include <utility>
#include <boost/intrusive/slist.hpp>
#include <glm/glm.hpp>

using namespace boost::intrusive;

struct unique_vbo {};

struct vertex_attribute : public slist_base_hook<link_mode<auto_unlink>> {
    int offset;
};

struct vertex_attribute_pack : public slist_base_hook<link_mode<auto_unlink>> {
    slist<vertex_attribute, constant_time_size<false>> attributes;
    int stride;
};

struct vertex_array {
    slist<vertex_attribute_pack, constant_time_size<false>> attribute_packs;
};

struct vertex_buffer {
    struct vertex_reference {
        vertex_buffer* b;
        int i;

        void* operator[] (vertex_attribute a);
    };

    vertex_reference operator[] (int i) {
        return {this, i};
    }
};

namespace typed {
    template<class T>
    struct vertex_attribute {
        vertex_attribute(int member_offset);

        operator const ::vertex_attribute() {
            return data;
        }

    private:
        // I think wrapping will cause fewer problems than inheriting
        ::vertex_attribute data;
        int member_offset, pack_offset;
    };

    template<class... T>
    struct vertex_attribute_pack : public ::vertex_attribute_pack {
        vertex_attribute_pack(unique_vbo& vbo, int stride, vertex_attribute<T>&... attributes);
    };

    template<class A>
    struct vertex_buffer {
        vertex_buffer(A, int capacity) = delete;
    };

    template<class... P>
    struct vertex_array : public ::vertex_array {
        friend struct vertex_buffer<vertex_array<P...>>;

        vertex_array(P&... attribute_packs);

        void push_back(vertex_buffer<vertex_array<P...>>&);
    };

    template<class... P>
    struct vertex_buffer<vertex_array<P...>> : public ::vertex_buffer {
        struct vertex_reference {
            vertex_buffer* b;
            int i;

            template<class T>
            T& operator[] (vertex_attribute<T> a);
        };

        vertex_buffer(vertex_array<P...>& array, int capacity);

        vertex_reference operator[] (int i) {
            return {this, i};
        }
    };
}


// creates a vbo through OpenGL
unique_vbo vbo;

// specify types and offsets of members
typed::vertex_attribute<glm::vec3> position(0);
typed::vertex_attribute<glm::vec3> normal(12);
typed::vertex_attribute<int> id(24);

// specify vbo, stride and members
typed::vertex_attribute_pack attributes(vbo, 32, position, normal, id);

// a vertex_array can have multiple vertex_attribute_pack from different vbos.
typed::vertex_array mesh(attributes);

void write_mesh() {
    // specify mesh and capacity
    typed::vertex_buffer buffer(mesh, 3);

    buffer[0][position] = {0, 0, 0};
    buffer[0][normal] = {0, 0, 1};
    buffer[0][id] = 15;
    buffer[1][position] = {1, 0, 0};
    buffer[1][normal] = {0, 0, 1};
    buffer[1][id] = 15;
    buffer[2][position] = {0, 1, 0};
    buffer[2][normal] = {0, 0, 1};
    buffer[2][id] = 15;

    mesh.push_back(buffer);
}



#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <memory>

#include <fast/collections/span.h>

#include "vertex_array.h"

namespace ge1 {

    struct vertex_buffer {
        struct pack_reference {
            friend vertex_buffer;

            void* operator[] (const vertex_attribute& a) const;

            char* get_data() const;

        private:
            pack_reference(char* data);

            char* data;
        };

        struct reference {
            friend vertex_buffer;

            pack_reference operator[] (const vertex_attribute_pack& p) const;
            void* operator[] (const vertex_attribute& a) const;

        private:
            reference(fast::unique_span<char>* data, int i);

            fast::unique_span<char>* data;
            int i;
        };

        vertex_buffer(const vertex_array_data& format, unsigned int capacity);

        unsigned int get_capacity() const;

        reference operator[] (int i);
        const fast::unique_span<char>& operator[](
            const vertex_attribute_pack& a
        ) const;

    private:
        fast::unique_span<fast::unique_span<char>> data;
        unsigned int capacity;
    };


    inline void* vertex_buffer::pack_reference::operator[](
        const vertex_attribute& a
    ) const {
        return data + a.get_offset();
    }

    inline char* vertex_buffer::pack_reference::get_data() const {
        return data;
    }

    inline vertex_buffer::pack_reference::pack_reference(
        char* data
    ) : data(data) {}

    inline vertex_buffer::pack_reference vertex_buffer::reference::operator[](
        const vertex_attribute_pack& p
    ) const {
        return {data[p.get_index()].begin() + i * p.get_stride()};
    }

    inline void* vertex_buffer::reference::operator[](
        const vertex_attribute& a
    ) const {
        auto p = a.get_pack();
        return
            data[p->get_index()].begin() + i * p->get_stride() + a.get_offset();
    }

    inline vertex_buffer::reference::reference(
        fast::unique_span<char>* data, int i
    ) : data(data), i(i) {}

    inline unsigned int vertex_buffer::get_capacity() const {
        return capacity;
    }

    inline vertex_buffer::reference vertex_buffer::operator[](int i) {
        return {data.begin(), i};
    }

    inline const fast::unique_span<char>& vertex_buffer::operator[](
        const vertex_attribute_pack& a
    ) const {
        return data[a.get_index()];
    }

}

#endif // VERTEX_BUFFER_H

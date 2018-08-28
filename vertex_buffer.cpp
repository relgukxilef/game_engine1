#include "vertex_buffer.h"

namespace ge1 {

    vertex_buffer::vertex_buffer(
        const vertex_array_data& format, unsigned int capacity
    ) : data(format.get_attribute_packs().size()), capacity(capacity) {

        auto d = data.begin();
        auto p = format.get_attribute_packs().begin();

        for (; d != data.end(); d++, p++) {
            *d = {static_cast<size_t>(p->get_stride()) * capacity};
        }
    }

}

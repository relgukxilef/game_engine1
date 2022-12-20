#pragma once

#include <glm/glm.hpp>

namespace ge1 {

    struct editor_io {
        glm::vec2 mouse_position, mouse_delta;

        bool mouse_left, mouse_middle, mouse_right;
        bool key_shift, key_ctrl, key_alt;

        bool captures_input;
    };
}

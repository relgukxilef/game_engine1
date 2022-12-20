#pragma once

#include <glm/glm.hpp>

#include "editor_io.h"

namespace ge1 {

    struct editor_camera {
        editor_camera();

        glm::mat4 get_view_matrix(glm::mat4 scene_view_matrix) const;

        void update(editor_io& io);

        glm::mat4 view_matrix;
        bool active = false;
    };

}

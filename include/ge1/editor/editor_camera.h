#pragma once

#include <glm/glm.hpp>

namespace ge1 {

    struct editor_camera {
        editor_camera();

        glm::mat4 get_view_matrix(glm::mat4 scene_view_matrix) const;
        void mouse_button(int button);
        void mouse_move(glm::vec2 position);

        glm::mat4 view_matrix;
        bool active = false;
    };

}

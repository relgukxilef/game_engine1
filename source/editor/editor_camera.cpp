#include "ge1/editor/editor_camera.h"

namespace ge1 {

    editor_camera::editor_camera() {
        view_matrix = glm::mat4(1);
    }

    glm::mat4 editor_camera::get_view_matrix(
        glm::mat4 scene_view_matrix
    ) const {
        if (active) {
            return view_matrix;
        } else {
            return scene_view_matrix;
        }
    }

    void editor_camera::mouse_button(int button) {

    }

    void editor_camera::mouse_move(glm::vec2 position) {

    }

}

#include "ge1/editor/editor_camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ge1 {

    glm::mat4 turntable_rotate(glm::mat4 m, glm::vec2 rotation, float depth) {
        m[3].z += depth;
        auto transposed = transpose(glm::mat3(m));
        auto center = -transposed * m[3];

        m = glm::rotate(m, rotation.x, {0, 0, 1});
        m = glm::rotate(m, rotation.y, {transpose(m)[0]});

        m[3] = glm::vec4(glm::mat3(m) * center, 1);
        m[3].z -= depth;
        return m;
    }

    editor_camera::editor_camera() {
        view_matrix = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0), {0, 0, 1});
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

    void editor_camera::update(editor_io &io) {
        if (io.key_alt) {
            if (io.mouse_left) {
                view_matrix = turntable_rotate(
                    view_matrix, io.mouse_delta * 0.01f, 5.f
                );
            }
        }
    }

}

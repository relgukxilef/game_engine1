#include "../include/ge1/composition.h"

namespace ge1 {

    composition::composition() {

    }

    void composition::render() {
        for (auto& pass : passes) {
            for (auto& renderable : pass.renderables) {
                renderable.render();
            }
        }
    }

}

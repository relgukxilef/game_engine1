#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "composition.h"
#include "typed/vertex_array.h"
#include "vertex_vector.h"
#include "resources.h"
#include "draw_call.h"
#include "program.h"
#include "vertex_buffer.h"
#include "typed/glm_types.h"

using namespace std;
using namespace glm;

using namespace ge1;

void window_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwSwapInterval(1);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    int screen_width = mode->width, screen_height = mode->height;

    window = glfwCreateWindow(
        screen_width, screen_height, "demo", nullptr, nullptr
    );
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    typed::vertex_attribute<glm::vec3, 0> position{GL_FALSE};
    typed::vertex_attribute<glm::vec3, 12> color{GL_FALSE};

    vertex_attribute_pack_vector mesh_data{{&position, &color}};

    vertex_vector mesh{&mesh_data};

    vertex_buffer buffer(mesh, 6);

    position(buffer[0]) = {-1, -1, 0};
    color(buffer[0]) = {0, 0, 1};
    position(buffer[1]) = {1, -1, 0};
    color(buffer[1]) = {1, 0, 1};
    position(buffer[2]) = {-1, 1, 0};
    color(buffer[2]) = {0, 1, 1};
    position(buffer[3]) = {-1, 1, 0};
    color(buffer[3]) = {0, 1, 1};
    position(buffer[4]) = {1, -1, 0};
    color(buffer[4]) = {1, 0, 1};
    position(buffer[5]) = {1, 1, 0};
    color(buffer[5]) = {1, 1, 1};

    mesh.push_back(buffer);

    unique_shader fragment_utils = compile_shader(
        GL_FRAGMENT_SHADER, "shaders/utils.fs"
    );

    unique_program solid = compile_program(
        "shaders/solid.vs", nullptr, nullptr, nullptr, "shaders/solid.fs",
        {fragment_utils.get_name()},
        {{"position", position}, {"color", color}}, {}
    );

    draw_call mesh_draw_call{&mesh, solid.get_name(), GL_TRIANGLES};


    composition composition;

    pass background_pass;
    pass foreground_pass;

    composition.passes.push_back(background_pass);
    composition.passes.push_back(foreground_pass);

    foreground_pass.renderables.push_back(mesh_draw_call);


    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetWindowSizeCallback(window, &window_size_callback);


    while (!glfwWindowShouldClose(window)) {
        composition.render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    cout << "Hello World!" << endl;
    return 0;
}

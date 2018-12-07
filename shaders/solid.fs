#version 410 core

in vec3 vertex_color;

out vec4 color;

vec3 rgb_to_srgb(vec3 rgb);

void main(void) {
    color = vec4(rgb_to_srgb(vertex_color), 1.0);
}

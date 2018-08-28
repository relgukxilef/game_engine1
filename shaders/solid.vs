#version 410 core

in vec3 position, color;

out vec3 vertex_color;

void main(void) {
	gl_Position = vec4(position, 1.0);
		//projection * view * model * vec4(position, 1.0);
	vertex_color = color;
}

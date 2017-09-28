#version 330 core
layout (location = 0) in vec3 vPosition;

uniform mat4 model;
uniform mat4 view_projection;

void main() {
	gl_Position = view_projection * model * vec4(vPosition, 1.0);
}
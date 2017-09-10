#version 330 core
layout (location = 0) in vec3 vPosition;

uniform mat4 model_view;
uniform mat4 projection;

void main() {
	// Projection * View * Model * vec4(Position.x, Position.y, Position.z, 1.0);
	gl_Position = projection * model_view * vec4(vPosition, 1);
}
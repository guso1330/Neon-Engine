#version 330 core

layout (location = 0) in vec3 vPosition;

struct Matrices
{
	mat4 view_projection;
};

uniform mat4 model;
uniform Matrices matrices;

void main() {
	gl_Position = matrices.view_projection * vec4(vec3(model * vec4(vPosition, 1.0)), 1.0);
}

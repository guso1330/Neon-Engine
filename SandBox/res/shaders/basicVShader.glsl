#version 330 core

layout (location = 0) in vec3 vPosition;

struct Matrices
{
	mat4 view;
	mat4 projection;
	mat4 view_projection;
};

uniform Matrices matrices;
uniform mat4 model;
uniform vec4 vcolor;

out vec4 fcolor;

void main() {
	gl_Position = matrices.view_projection * model * vec4(vPosition, 1.0);

	fcolor = vcolor;
}
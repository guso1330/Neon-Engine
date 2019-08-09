#version 330 core

layout (location = 0) in vec3 vPosition;

out vec4 fcolor;

uniform mat4 model;
uniform mat4 view_projection;
uniform vec4 vcolor;


void main() {
	gl_Position = view_projection * model * vec4(vPosition, 1.0);

	fcolor = vcolor;
}
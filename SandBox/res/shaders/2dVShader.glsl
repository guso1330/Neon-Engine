#version 330 core

layout (location = 0) in vec3 vPosition;

uniform vec4 vcolor;

out vec4 fcolor;

void main() {
	gl_Position = vec4(vPosition, 1.0);

	fcolor = vcolor;
}
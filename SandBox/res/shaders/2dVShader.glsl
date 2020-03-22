#version 330 core

layout (location = 0) in vec3 vPosition;

uniform vec2 screenSize;

void main() {
	gl_Position.x = (1.0 / screenSize.x) * (vPosition.x);
	gl_Position.y = (1.0 / screenSize.y) * (vPosition.y);
	gl_Position.z = (1.0 / 1.0) * (vPosition.z);
	gl_Position.w = 1.0;
}

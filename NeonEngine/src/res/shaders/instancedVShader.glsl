#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in mat4 transform;

out vec4 fcolor;
out vec2 texFrag;

uniform mat4 model;
uniform mat4 view_projection;
uniform vec4 vcolor;

void main() {
	gl_Position = view_projection * model * transform * vec4(vPosition, 1.0);
	fcolor = vcolor;
	texFrag = texCoord;
}
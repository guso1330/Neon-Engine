#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 vNormal;

out vec4 fcolor;
out vec2 texFrag;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 normal_matrix;
uniform mat4 view_projection;
uniform vec4 vcolor;

void main() {
	fcolor = vcolor;
	texFrag = texCoord;
	fragPos = vec3(model * vec4(vPosition, 1.0));
	// Creates the Normal Model Matrix
	// TODO: inverse matrix calculations are very costly operations so do 
	// this on the CPU and send it over instead.
	normal = mat3(normal_matrix) * vNormal;

	gl_Position = view_projection * vec4(fragPos, 1.0);
}
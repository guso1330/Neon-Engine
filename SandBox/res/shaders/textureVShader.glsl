#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in vec3 vNormal;

struct Matrices
{
	mat4 view;
	mat4 projection;
	mat4 view_projection;
};

uniform Matrices matrices;

uniform	mat4 model;
uniform vec4 vcolor;

out vec4 fcolor;
out vec2 texFrag;
// out vec3 normal;
out vec3 fragPos;

void main() {
	fcolor = vcolor;
	texFrag = vTexCoord;
	fragPos = vec3(model * vec4(vPosition, 1.0));

	gl_Position = matrices.view_projection * vec4(fragPos, 1.0);
}

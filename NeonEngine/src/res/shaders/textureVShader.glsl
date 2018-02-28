#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 vNormal;

out vec4 fcolor;
out vec2 texFrag;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view_projection;
uniform vec4 vcolor;

void main() {
	fragPos = vec3(model * vec4(vPosition, 1.0));
	fcolor = vcolor;
	texFrag = texCoord;
	normal = mat3(transpose(inverse(model))) * vNormal;;
	gl_Position = view_projection * vec4(fragPos, 1.0);
}
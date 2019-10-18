#version 330 core
in vec4 fcolor;
in vec2 texFrag;
in vec3 fragPos;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;

out vec4 out_FragColor;

void main() {
	
	// Final color
	vec4 result = fcolor * texture(textureSampler, texFrag).rgba;
	
	out_FragColor = result;
}

#version 330 core
in vec4 fcolor;
in vec2 texFrag;

struct Material {
	vec3 ambient;
	sampler2D diffuse;
};

struct AmbientLight {
	float intensity;
	vec3 diffuse;
};

uniform Material material;
uniform AmbientLight light;

out vec4 out_FragColor;

void main() {

	// Ambient Color
	vec3 ambient = (vec3(texture(material.diffuse, texFrag)) * material.ambient * light.diffuse) * light.intensity;

	// Final color
	vec4 result = fcolor * vec4(ambient, 1.0);
	
	out_FragColor = result;
}
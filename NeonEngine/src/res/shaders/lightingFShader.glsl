#version 330 core
in vec4 fcolor;
in vec2 texFrag;
in vec3 normal;
in vec3 fragPos;

struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
	sampler2D height;
	sampler2D occlusion;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

out vec4 out_FragColor;

void main() {
	float intensity = 100.0f;
	float distance = distance(light.position, fragPos);

	// Ambient Color
	vec3 ambient = light.ambient * material.ambient * vec3(texture(material.diffuse, texFrag));

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texFrag)) * (intensity / distance);

	// Specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texFrag)) * (intensity / distance);
	
	// Final color
	vec4 result = vec4((ambient + diffuse + specular), 1.0) * fcolor;
	
	out_FragColor = result;
}
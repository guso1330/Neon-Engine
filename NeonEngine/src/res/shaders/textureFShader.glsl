#version 330 core
in vec4 fcolor;
in vec2 texFrag;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 out_FragColor;

void main() 
{
	// Ambient Color
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	// Final color
	vec4 result = vec4((ambient + diffuse), 1.0) * fcolor * texture(tex, texFrag);
	
	out_FragColor = result;
}

// #version 330 core
// in vec4 fcolor;
// in vec2 texFrag;
// in vec3 normal;
// in vec3 fragPos;

// uniform sampler2D tex;
// uniform vec3 lightColor;
// uniform vec3 lightPos;

// out vec4 out_FragColor;

// void main() 
// {
// 	// Ambient Color
// 	float ambientStrength = 0.1;
// 	vec3 ambient = ambientStrength * lightColor;

// 	// Diffuse
// 	vec3 norm = normalize(normal);
// 	vec3 lightDir = normalize(lightPos - fragPos);
// 	float diff = max(dot(norm, lightDir), 0.0);
// 	vec3 diffuse = diff * lightColor;

// 	// Final color
// 	vec4 result = vec4((ambient + diffuse), 1.0) * fcolor * texture(tex, texFrag);
	
// 	out_FragColor = result;
// }
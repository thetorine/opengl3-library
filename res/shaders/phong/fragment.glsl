#version 330 core

in vec2 texPos;
in vec3 m;
in vec4 viewPos;

out vec4 color;

uniform mat4 viewMatrix;

uniform sampler2D tex;
uniform bool wireframe;
uniform vec3 lightPos;

uniform vec3 lightIntensity;
uniform float ambientCoeff;
uniform float diffuseCoeff;
uniform float specularCoeff;
uniform float phongExp;

void main() {
	vec3 s = (viewMatrix * vec4(lightPos, 1) - viewPos).xyz;
	vec3 r = normalize(-s + 2 * dot(s, m) * m);
	vec3 v = normalize(-viewPos.xyz); // in view coords - camera at (0, 0, 0)
	
	vec3 ambient = lightIntensity * ambientCoeff;

	float dotResult = dot(m, normalize(s));
	vec3 diffuse = vec3(0.0f);
	diffuse = max(lightIntensity * diffuseCoeff * dotResult, 0.0f);

	vec3 specular = vec3(0.0);
	if (dotResult > 0)
		specular = max(vec3(pow(specularCoeff * dot(r, v), phongExp)), 0.0f);

	vec3 lightSum = ambient + diffuse + specular;

	color = vec4(lightSum, 1.0);
}

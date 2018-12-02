#version 330 core

#define LIGHT_SOURCE_COUNT 2

struct point_light {
	vec3 pos;
	vec3 color;
	float intensity;
	bool on;
};

in vec3 m;
in vec4 viewPos;

out vec4 fragmentColor;

uniform mat4 viewMatrix;

uniform point_light pointLights[LIGHT_SOURCE_COUNT];

uniform float ambientCoeff;
uniform float diffuseCoeff;
uniform float specularCoeff;
uniform float phongExp;

uniform vec3 ambientIntensity;
uniform vec3 diffuseIntensity;

vec3 getPhongIntensity(vec3 s, vec3 v, vec3 color, float intensity);

void main() {
	vec3 v = normalize(-viewPos.xyz);

	vec3 colorSum = vec3(0.0);
	for (int i = 0; i < LIGHT_SOURCE_COUNT; i++) {
		if (!pointLights[i].on) continue;
		vec3 s = (viewMatrix * vec4(pointLights[i].pos, 1.0) - viewPos).xyz;
		colorSum += getPhongIntensity(s, v, pointLights[i].color, pointLights[i].intensity);
	}
	
	fragmentColor = vec4(colorSum, 1.0);
}

vec3 getPhongIntensity(vec3 s, vec3 v, vec3 color, float intensity) {
	vec3 r = normalize(reflect(-s, m));
	float dotResult = dot(m, normalize(s));

	vec3 ambient = ambientIntensity * ambientCoeff * color * intensity;
	vec3 diffuse = max(diffuseIntensity * diffuseCoeff * color * intensity * dotResult, 0.0);
	vec3 specular = vec3(0.0);

	if (dotResult > 0)
		specular = vec3(max(pow(specularCoeff * dot(r, v), phongExp), 0.0));

	return ambient + diffuse + specular;
}
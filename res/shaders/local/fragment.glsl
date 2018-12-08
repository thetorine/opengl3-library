#version 330 core

#define LIGHT_SOURCE_COUNT 2
#define PHONG_SHADER 0
#define BLINN_SHADER 1
#define CEL_SHADER 2

// Incoming from vertex shader
in vec3 m;
in vec4 viewPos;

// Outgoing from fragment shader
out vec4 fragmentColor;

// Matrices
uniform mat4 viewMatrix;

// Light source properties
struct directional_light {
    vec3 dir;
    vec3 color;
    float intensity;
    bool on;
};
uniform directional_light directionalLights[LIGHT_SOURCE_COUNT];

struct point_light {
    vec3 pos;
    vec3 color;
    float intensity;
    bool on;
};
uniform point_light pointLights[LIGHT_SOURCE_COUNT];

struct spotlight {
    vec3 pos;
    vec3 dir;
    vec3 color;
    float intensity;
    float cutoff;
    float attenPow;
    bool on;
};
uniform spotlight spotlights[LIGHT_SOURCE_COUNT];

// Material properties
uniform float ambientCoeff;
uniform float diffuseCoeff;
uniform float specularCoeff;
uniform float phongExp;

// The reflective properties of the material
// How much does the material reflect for each RGB component
uniform vec3 ambientIntensity;
uniform vec3 diffuseIntensity;

// 0 = Phong, 1 = Cel
uniform int shaderType;

vec3 getIntensity(vec3 s, vec3 v, vec3 color, float intensity);
vec3 getPhongIntensity(vec3 s, vec3 v, vec3 color, float intensity);
vec3 getCelIntensity(vec3 s, vec3 v, vec3 color, float intensity);
vec3 getBlinnIntensity(vec3 s, vec3 v, vec3 color, float intensity);

void main() {
    vec3 v = normalize(-viewPos.xyz);

    vec3 colorSum = vec3(0.0);
    for (int i = 0; i < LIGHT_SOURCE_COUNT; i++) {
        if (!pointLights[i].on) continue;
        vec3 s = (viewMatrix * vec4(pointLights[i].pos, 1.0) - viewPos).xyz;
        colorSum += getIntensity(s, v, pointLights[i].color, pointLights[i].intensity);
    }

    for (int i = 0; i < LIGHT_SOURCE_COUNT; i++) {
        if (!directionalLights[i].on) continue;
        vec3 s = (viewMatrix * vec4(directionalLights[i].dir, 0.0)).xyz;
        colorSum += getIntensity(s, v, directionalLights[i].color, directionalLights[i].intensity);
    }

    for (int i = 0; i < LIGHT_SOURCE_COUNT; i++) {
        if (!spotlights[i].on) continue;
        vec3 s = (viewMatrix * vec4(spotlights[i].pos, 1.0) - viewPos).xyz;
        vec3 f = (viewMatrix * vec4(spotlights[i].dir, 0.0)).xyz;

        float sfDot = dot(normalize(-s), normalize(f));
        if (acos(sfDot) <= radians(spotlights[i].cutoff / 2.0)) { 
            colorSum += pow(sfDot, spotlights[i].attenPow) * getIntensity(s, v, spotlights[i].color, spotlights[i].intensity);
        }
    }
    
    fragmentColor = vec4(colorSum, 1.0);
}

vec3 getIntensity(vec3 s, vec3 v, vec3 color, float intensity) {
    switch (shaderType) {
        case PHONG_SHADER: return getPhongIntensity(s, v, color, intensity);
        case CEL_SHADER: return getCelIntensity(s, v, color, intensity);
        case BLINN_SHADER: return getBlinnIntensity(s, v, color, intensity); 
    }
    return vec3(0.0);
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

vec3 getCelIntensity(vec3 s, vec3 v, vec3 color, float intensity) {
    vec3 r = normalize(reflect(-s, m));
    float dotResult = dot(m, normalize(s));

    vec3 ambient = ambientIntensity * ambientCoeff * color * intensity;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    if (dotResult > 0) {
        float diffuseTerm = dotResult;
        float specularTerm = pow(specularCoeff * dot(r, v), phongExp);

        int bands = 3;
        diffuse = round(diffuseTerm * bands) / bands * diffuseIntensity * diffuseCoeff * color * intensity;

        if (specularTerm > 0.5)
            specular = vec3(max(pow(specularCoeff, phongExp), 0.0));
    }

    vec3 sum = ambient + diffuse + specular;
    if (dot(v, m) < mix(0.2, 0.35, max(0.0, dotResult)))
        sum = vec3(0.0);

    return sum;
}

vec3 getBlinnIntensity(vec3 s, vec3 v, vec3 color, float intensity) {
    vec3 h = normalize((normalize(s) + v) / 2.0);
    float dotResult = dot(m, normalize(s));

    vec3 ambient = ambientIntensity * ambientCoeff * color * intensity;
    vec3 diffuse = max(diffuseIntensity * diffuseCoeff * color * intensity * dotResult, 0.0);
    vec3 specular = vec3(0.0);

    if (dotResult > 0)
        specular = vec3(max(pow(specularCoeff * dot(h, m), phongExp * 2.0), 0.0));

    return ambient + diffuse + specular;
}
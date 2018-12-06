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
    vec3 specular = vec3(0.0f);
    if (dotResult > 0) {
        float diffuseTerm = dotResult;
        float specularTerm = pow(specularCoeff * dot(r, v), phongExp);
        if (diffuseTerm > 0.9)
            diffuse = lightIntensity;
        else if (diffuseTerm > 0.6)
            diffuse = 0.7 * lightIntensity;
        else if (diffuseTerm > 0.3)
            diffuse = 0.4 * lightIntensity;
        if (specularTerm > 0.5)
            specular = vec3(1.0) * max(pow(specularCoeff, phongExp), 0.0f);
    } 

    if (dot(v, m) < mix(0.2, 0.35, max(0.0, dotResult))) {
        color = vec4(0.3 * lightIntensity, 1.0);
    } else {
        vec3 lightSum = ambient + diffuse + specular;
        color = vec4(lightSum, 1.0);
    }	
}

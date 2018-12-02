#include "lighting.hpp"

#include <stdio.h>

lighting::lighting() {
}

lighting::~lighting() {

}

void lighting::addPointLight(glm::vec3 pos, glm::vec3 color, float intensity) {
	pointLightList.push_back(point_light(pos, color, intensity));
}

void lighting::addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity) {

}

void lighting::setShaderType(int type) {
	shader::getInstance()->setInt("shaderType", type);
}

void lighting::updateShader() {
	for (int i = 0; i < pointLightList.size(); i++) {
		char buffer[16];
		snprintf(buffer, sizeof(buffer), "pointLights[%d]", i);
		std::string structName = buffer;

		shader::getInstance()->setVec3(structName + ".pos", pointLightList[i].getPos());
		shader::getInstance()->setVec3(structName + ".color", pointLightList[i].getColor());
		shader::getInstance()->setFloat(structName + ".intensity", pointLightList[i].getIntensity());
		shader::getInstance()->setInt(structName + ".on", true);
	}
}

void lighting::setMaterialCoeffs(float ambient, float diffuse, float specular, float phongExp) {
	shader::getInstance()->setFloat("ambientCoeff", ambient);
	shader::getInstance()->setFloat("diffuseCoeff", diffuse);
	shader::getInstance()->setFloat("specularCoeff", specular);
	shader::getInstance()->setFloat("phongExp", phongExp);
}

void lighting::setMaterialIntensities(glm::vec3 ambient, glm::vec3 diffuse) {
	shader::getInstance()->setVec3("ambientIntensity", ambient);
	shader::getInstance()->setVec3("diffuseIntensity", diffuse);
}
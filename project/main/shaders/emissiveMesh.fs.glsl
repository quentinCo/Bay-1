#version 330

#define MAX_LIGHTS 100

struct Material{
	vec3 diffuseColor;
	vec3 ambientColor;
	vec3 specularColor;
	vec3 emissionColor;
	
	float shininess;
	float opacity;
};

uniform Material uMaterial;
uniform mat4 uMVMatrix;

in vec3 vPosition_vs;
in vec3 vNormal_vs;

out vec3 fFragColor;

void main() {
	vec3 wo = normalize(-vPosition_vs);
	vec3 N = vNormal_vs;

	fFragColor = uMaterial.emissionColor * 100 * dot((vec3(0,0,1) + N)*0.5,N);
}

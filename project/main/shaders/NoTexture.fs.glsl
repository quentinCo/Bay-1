#version 330


struct Material{
	vec3 diffuseColor;
	vec3 ambientColor;
	vec3 specularColor;
	vec3 emissionColor;
	
	float shininess;
	float opacity;
};


uniform Material uMaterial;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vCoordsTex;


out vec3 fFragColor;


void main() {
	fFragColor = uMaterial.diffuseColor;
	//fFragColor = uMaterial.ambientColor;
	//fFragColor = uMaterial.specularColor;
	//fFragColor = uMaterial.emissionColor;
	//fFragColor = vec3(1,0,0);
}

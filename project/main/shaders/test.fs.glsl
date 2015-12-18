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
uniform sampler2D uTexture_diffuse1;
uniform sampler2D uTexture_normal1;
uniform sampler2D uTexture_specular1;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vCoordsTex;


out vec3 fFragColor;


void main() {
	//fFragColor = uMaterial.diffuseColor;
	//fFragColor = uMaterial.ambientColor;
	//fFragColor = uMaterial.specularColor;
	//fFragColor = uMaterial.emissionColor;
	
	//fFragColor = vPosition;
	
	//fFragColor = vec3(vCoordsTex,0);
	
	//fFragColor = texture(uTexture_diffuse1, vCoordsTex).xyz;
	
	//fFragColor = texture(uTexture_normal1, vCoordsTex).xyz;
	
	//fFragColor = texture(uTexture_specular1, vCoordsTex).xyz;
	
	//fFragColor = normalize(vNormal);
	
	//fFragColor = vec3(0,1,0);
}

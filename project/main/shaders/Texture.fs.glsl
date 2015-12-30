#version 330

#define MAX_LIGHTS 100

struct EllipsoidLight{
	vec4 position;
	vec4 halfAxes;
	vec4 lightIntensity;
};

struct DirectionalLight{
	vec4 direction;
	vec4 lightIntensity;
};

struct Material{
	vec3 diffuseColor;
	vec3 ambientColor;
	vec3 specularColor;
	vec3 emissionColor;
	
	float shininess;
	float opacity;
};

layout (std140) uniform uEllipsoidLigths {
	EllipsoidLight eLights[MAX_LIGHTS];
};

uniform int uEllipsoidLigths_nb;

layout (std140) uniform uDirectionalLights {
	DirectionalLight dLights[MAX_LIGHTS];
};

uniform int uDirectionalLights_nb;

uniform Material uMaterial;
uniform sampler2D uTexture_diffuse1;
uniform sampler2D uTexture_normal1;
uniform sampler2D uTexture_specular1;
uniform mat4 uMVMatrix;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vCoordsTex;


out vec3 fFragColor;

vec3 blinnPhong(){
	vec3 wi;
	float d;
	vec3 Li;
	vec3 wo = normalize(-vPosition_vs);
	vec3 N;
	vec3 normalMapTexel = texture(uTexture_normal1, vCoordsTex).xyz;
	vec3 diffuseMapTexel = texture(uTexture_diffuse1, vCoordsTex).xyz;
	vec3 specularMapTexel = texture(uTexture_specular1, vCoordsTex).xyz;
	
	float shininess = max(uMaterial.shininess, 1000);
	
	vec3 MVLightPosition ; //Position de la lumière dans le repère caméra
	
	if(normalMapTexel != vec3(0, 0, 0)){
		N = mat3(vNormal_vs, vec3(0), vec3(0)) * normalMapTexel;
	}
	else{
		N = vNormal_vs;
	}
		
	vec3 halfVector;
	
	vec3 traceVec;
	
	vec3 finalColor;
	
	for(int i = 0; i < uEllipsoidLigths_nb ; ++i){
		MVLightPosition = (uMVMatrix * eLights[i].position).xyz;
		
		wi = normalize(MVLightPosition - vPosition_vs);
		
		traceVec = normalize((inverse(uMVMatrix) * vec4(vPosition_vs, 1) - eLights[i].position).xyz); //Vecteur entre la lumière et le fragment dans le repère absolu du monde
		
		d = distance(MVLightPosition, vPosition_vs) * length(vec3(traceVec.x/eLights[i].halfAxes.x, traceVec.y/ eLights[i].halfAxes.y, traceVec.z/eLights[i].halfAxes.z)); //On étire la lumière sur les trois axes x,y et z
		
		Li = eLights[i].lightIntensity.xyz / (d*d);
		
		halfVector = (wo + wi) * 0.5;
		
		finalColor += Li * (diffuseMapTexel * max(0,dot(wi, N)) + specularMapTexel * pow(max(0,dot(halfVector, N)), shininess));
	}
	
	for(int i = 0; i < uDirectionalLights_nb ; ++i){
		wi = normalize((uMVMatrix * dLights[i].direction).xyz);
		Li = dLights[i].lightIntensity.xyz;
		halfVector = (wo + wi) * 0.5;
		
		finalColor += Li * (diffuseMapTexel * max(0,dot(wi, N)) + specularMapTexel * pow(max(0,dot(halfVector, N)), shininess));
	}
	
	return max(finalColor, uMaterial.ambientColor) + uMaterial.emissionColor;
}

void main() {

	fFragColor = blinnPhong();
	
}

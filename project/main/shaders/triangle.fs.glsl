#version 330

#define MAX_LIGHTS 10

uniform struct EllipsoidLight{
	vec3 position;
	vec3 halfAxes;
	vec3 lightIntensity;
};

layout (std140) uniform uAllEllipsoidLigths {
	EllipsoidLight lights [MAX_LIGHTS];
};

in vec3 vDiffColor;
in vec3 vNormal;
in vec3 vAmbColor;
in vec3 vSpecColor;
in vec3 vEmiColor;
in vec3 vVertexPosition;
in vec3 vVertexNormal;

uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightPos; //A supprimer
uniform vec3 uHalfAxes; //A supprimer
uniform vec3 uAxeX; //A supprimer
uniform vec3 uAxeY; //A supprimer
uniform vec3 uLightIntensity;
uniform mat4 uCamera;
uniform int uNumLights;

out vec3 fFragColor;

vec3 blinnPhong(){
	
	vec3 wi = normalize(uLightDir_vs);
	vec3 Li = uLightIntensity;
	vec3 wo = normalize(-vVertexPosition);
	vec3 N = normalize(vVertexNormal);
	vec3 halfVector = (wo + wi) * 0.5;
	
	return Li * (vDiffColor * max(0,dot(wi, N)) + vSpecColor * pow(max(0,dot(halfVector, N)), uShininess));
}

vec3 blinnPhongLights(){
	vec3 wi;
	float d;
	vec3 Li;
	vec3 wo = normalize(-vVertexPosition);
	vec3 N = normalize(vVertexNormal);
	vec3 halfVector;
	
	vec3 traceVec;
	
	vec3 finalColor;
	
	//Test une lumière---------------------------------------
	wi = normalize(uLightPos - vVertexPosition);
	
	traceVec = normalize((inverse(uCamera) * vec4(vVertexPosition, 1)).xyz - uLightPos);
	
	d = distance((uCamera * vec4(uLightPos, 1)).xyz, vVertexPosition)*length(vec3(traceVec.x/uHalfAxes.x, traceVec.y/ uHalfAxes.y, traceVec.z/uHalfAxes.z));
	
	Li = uLightIntensity / (d*d);
	
	halfVector = (wo + wi) * 0.5;
	
	finalColor += Li * (vDiffColor * max(0,dot(wi, N)) + vSpecColor * pow(max(0,dot(halfVector, N)), uShininess));
	//Fin test-----------------------------------------------
	
	/*for(int i = 0; i < numLights ; ++i){
		wi = normalize(allEllipsoidLigths[i].position - vVertexPosition);
		
		cosTheta = dot(wi, vec3(1,0,0)) / (length(wi) * length(vec3(1,0,0)));
		cosPhi = dot(wi, vec3(0,1,0)) / (length(wi) * length(vec3(0,1,0)));
		sinTheta = cross(wi, vec3(1,0,0)) / (length(wi) * length(vec3(1,0,0)));
		sinPhi = cross(wi, vec3(0,1,0)) / (length(wi) * length(vec3(0,1,0)));
		
		ellipsoidPoint.x = allEllipsoidLigths[i].halfAxes.a * cosTheta * cosPhi;
		ellipsoidPoint.y = allEllipsoidLigths[i].halfAxes.b * cosTheta * sinPhi;
		ellipsoidPoint.z = allEllipsoidLigths[i].halfAxes.c * sinTheta;
		
		d = distance(ellipsoidPoint, vVertexPosition);
		
		Li = allEllipsoidLigths[i].lightIntensity / (d*d);
		
		halfVector = (wo + wi) * 0.5;
		
		finalColor += Li * (vDiffColor * max(0,dot(wi, N)) + vSpecColor * pow(max(0,dot(halfVector, N)), uShininess));
	}*/
	return finalColor;
}

vec3 blinnPhongTest(){
	
	vec3 wi = normalize(uLightPos - vVertexPosition);
	float d = distance(uLightPos, vVertexPosition);
	vec3 Li = uLightIntensity / d*d;
	vec3 wo = normalize(-vVertexPosition);
	vec3 N = normalize(vVertexNormal);
	vec3 halfVector = (wo + wi) * 0.5;
	
	return Li * (vDiffColor * max(0,dot(wi, N)) + vSpecColor * pow(max(0,dot(halfVector, N)), uShininess));
}

void main() {
	//fFragColor = vDiffColor;
	//fFragColor = vAmbColor;
	//fFragColor = vSpecColor;
	//fFragColor = vEmiColor;
	
	//fFragColor = normalize(vNormal);
	
	fFragColor = blinnPhongLights();
	
	//fFragColor = vec3(0,1,0);
}

#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexDiffuseColor;
layout(location = 2) in vec3 aVertexNormal;
layout(location = 3) in vec3 aVertexAmbColor;
layout(location = 4) in vec3 aVertexSpecularColor;
layout(location = 5) in vec3 aVertexEmissionColor;

layout(location = 6) in float aVertexShininess;
layout(location = 7) in float aVertexOpacity;

out vec3 vDiffColor;
out vec3 vNormal;
out vec3 vAmbColor;
out vec3 vSpecColor;
out vec3 vEmiColor;

out vec3 vPosition;

mat4 rotate(float a, float b){
	return mat4(
		vec4(cos(radians(a))*cos(radians(b)), sin(radians(a))*cos(radians(b)), sin(radians(b)), 0),
		vec4(-sin(radians(a)), cos(radians(a)), 0, 0),
		vec4(cos(radians(a))*sin(radians(b)), sin(radians(a))*sin(radians(b)), cos(radians(b)), 0),
		vec4(0, 0, 0, 1)
	);
}

void main() {
	vDiffColor = aVertexDiffuseColor;
	vNormal = aVertexNormal;
	vAmbColor = aVertexAmbColor;
	vSpecColor = aVertexSpecularColor;
	vEmiColor = aVertexEmissionColor;
	
	vPosition = aVertexPosition;
	
	gl_Position = vec4(0.5*aVertexPosition.x, 0.5*aVertexPosition.y, 0.5*aVertexPosition.z, 1);
}

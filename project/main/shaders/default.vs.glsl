#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexCoordsTexture;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs;
out vec3 vNormal_vs; 
out vec2 vCoordsTex;

mat4 rotate(float a, float b){
	return mat4(
		vec4(cos(radians(a))*cos(radians(b)), sin(radians(a))*cos(radians(b)), sin(radians(b)), 0),
		vec4(-sin(radians(a)), cos(radians(a)), 0, 0),
		vec4(cos(radians(a))*sin(radians(b)), sin(radians(a))*sin(radians(b)), cos(radians(b)), 0),
		vec4(0, 0, 0, 1)
	);
}

void main() {
	// Passage en coordonnées homogènes
	vec4 vertexPosition = vec4(aVertexPosition, 1);
	vec4 vertexNormal = vec4(aVertexNormal, 0);

	// Calcul des valeurs de sortie
	vPosition_vs = vec3(uMVMatrix * vertexPosition);
	vNormal_vs = vec3(uNormalMatrix * vertexNormal);
	
	vCoordsTex = aVertexCoordsTexture;

	// Calcul de la position projetée
	
	gl_Position = uMVPMatrix*vec4(0.6*aVertexPosition.x, 0.6*aVertexPosition.y - 0.5, 0.6*aVertexPosition.z, 1);
}
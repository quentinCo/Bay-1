#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexCoordsTexture;

out vec3 vPosition;
out vec3 vNormal;
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
	vPosition = aVertexPosition;
	vNormal = aVertexNormal;
	vCoordsTex = aVertexCoordsTexture;
	
	gl_Position = vec4(0.6*aVertexPosition.x, 0.6*aVertexPosition.y - 0.5, 0.6*aVertexPosition.z, 1);
}

#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vCoordsTex;


out vec3 fFragColor;


void main() {
	fFragColor = vec3(0,1,0);

	//fFragColor = vPosition_vs;
}

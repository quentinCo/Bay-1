#version 330

in vec3 vDiffColor;
in vec3 vNormal;
in vec3 vAmbColor;
in vec3 vSpecColor;
in vec3 vEmiColor;

out vec3 fFragColor;


void main() {
	//fFragColor = vDiffColor;
	//fFragColor = vAmbColor;
	//fFragColor = vSpecColor;
	//fFragColor = vEmiColor;
	
	fFragColor = normalize(vNormal);
	
	//fFragColor = vec3(0,1,0);
}

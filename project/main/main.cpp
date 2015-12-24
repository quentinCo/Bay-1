// Import lib C++
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// Import glimac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/TrackballCamera.hpp>

// Import GL
#include <GL/glew.h>

// Import assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Import gtest
#include <gtest/gtest.h>

// Import
#include <libPerso/Vertex.hpp>
#include <libPerso/Mesh.hpp>

using namespace glimac;
using namespace glm;
using namespace std;

#define MAX_LIGHTS 10

#define M_PI 3.14159265358979323846

struct EnvironmentProgram {
    Program m_Program;

	GLint uMVPMatrix;
	GLint uMVMatrix;
	GLint uNormalMatrix;
	GLint uShininess;
	GLint uLightDir_vs;
	GLint uLightIntensity;
	GLint uLightPos; //A supprimer
	GLint uHalfAxes; //A supprimer
	GLint uAxeX; //A supprimer
	GLint uAxeY; //A supprimer
	GLint uCamera;
	GLint uNumLights;
	GLint uAllEllipsoidLigths;

    
    EnvironmentProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl",
							  applicationPath.dirPath() + "shaders/triangle.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
        uLightPos = glGetUniformLocation(m_Program.getGLId(), "uLightPos"); //A supprimer
        uHalfAxes = glGetUniformLocation(m_Program.getGLId(), "uHalfAxes"); //A supprimer
        uAxeX = glGetUniformLocation(m_Program.getGLId(), "uAxeX"); //A supprimer
        uAxeY = glGetUniformLocation(m_Program.getGLId(), "uAxeY"); //A supprimer
        uCamera = glGetUniformLocation(m_Program.getGLId(), "uCamera");
        uNumLights = glGetUniformLocation(m_Program.getGLId(), "uNumLights");
        uAllEllipsoidLigths = glGetUniformBlockIndex(m_Program.getGLId(), "uAllEllipsoidLigths");
    }
};

struct VectorProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uColor;
    
    VectorProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl",
							  applicationPath.dirPath() + "shaders/vector3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uColor = glGetUniformLocation(m_Program.getGLId(), "uColor");
    }
};

struct EllipsoidLight{
	vec3 position;
	vec3 halfAxes;
	vec3 lightIntensity;
	static int numLights;
	EllipsoidLight(){
		numLights++;
	}
};

int main(int argc, char** argv) {
	
	bool printDebug;
	if(argc > 1 && std::string(argv[1]).compare("debug")==0){
		std::cout<<"MODE PRINT_DEBUG\n"<<std::endl;
		printDebug = true;
	}
	else{
		printDebug = false;
	}

	// Initialize SDL and open a window
	float width = 1200;
    float height = 600;
    
	SDLWindowManager windowManager((int) width, (int) height, "GLImac");

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	/*********************************
	* HERE SHOULD COME THE INITIALIZATION CODE
	*********************************/
	
	glEnable(GL_DEPTH_TEST);
	
	mat4 ProjMatrix;
    mat4 MVMatrix;
    mat4 NormalMatrix;
	
	ProjMatrix = perspective(radians(70.f), width/height, 0.1f, 100.f);
	
	// Shader
	FilePath applicationPath(argv[0]);
		EnvironmentProgram environmentProgram(applicationPath);
		VectorProgram vectorProgram(applicationPath);


	// Verif existance fichier
	//std::string pathFile = "/home/corentin/Bay-1/project/main/assets/models/borderland/Maya/maya.obj";
	//std::string pathFile = "/home/corentin/Bay-1/project/main/assets/models/forme_test_collor.obj";
	//std::string pathFile = "/home/corentin/Bay-1/project/main/assets/models/Cavern.obj";
	std::string pathFile = "/home/corentin/Bay-1/project/main/assets/models/Rubik.obj";
	
	std::ifstream fin(pathFile.c_str());
	
	Assimp::Importer aImporter;
	
	if(!fin.fail()) {
		std::cout<< "Could open file: " << pathFile << std::endl;
		fin.close();
	}
	else{
		std::cerr<< "Couldn't open file: " << pathFile<<" \n" << aImporter.GetErrorString() << std::endl;
		return EXIT_FAILURE;
	}
	// ------------------------
	// Chargement scene
	const aiScene* aScene = aImporter.ReadFile(pathFile, aiProcess_Triangulate);
	if(aScene){
		std::cout << "Loading file : "<< pathFile <<std::endl;
	}
	else{
		std::cerr << "Error loading file : "<< pathFile <<" : " << aImporter.GetErrorString() <<std::endl;
		return EXIT_FAILURE;
	}	
	// ------------------------
	// Print Test
	if(printDebug){
		std::cout << "INFORMATION MESHS CHARGES\n"<<std::endl;
		for(int i = 0; i < aScene->mNumMeshes; i++){
			std::cout << "Mesh : " << i << " - Adress : "<< aScene->mMeshes[i] << std::endl;
			std::cout << "Point du mesh :" << std::endl;
			for(int j = 0; j < aScene->mMeshes[i]->mNumVertices; j++){
				std::cout <<"----> [" << aScene->mMeshes[i]->mVertices[j].x
				<<" , "<< aScene->mMeshes[i]->mVertices[j].y
				<<" , "<< aScene->mMeshes[i]->mVertices[j].z
				<<"]"<< std::endl;
			}
			std::cout << "Face du mesh :"<< std::endl;
			for(int j = 0; j < aScene->mMeshes[i]->mNumFaces; j++){
				std::cout <<"Face "<< j <<" : "<<std::endl;
				for(int k = 0; k < aScene->mMeshes[i]->mFaces[j].mNumIndices; k++){
					std::cout <<"----> "<< aScene->mMeshes[i]->mFaces[j].mIndices[k]
					<< "[" << aScene->mMeshes[i]->mVertices[aScene->mMeshes[i]->mFaces[j].mIndices[k]].x
					<<" , "<< aScene->mMeshes[i]->mVertices[aScene->mMeshes[i]->mFaces[j].mIndices[k]].y
					<<" , "<< aScene->mMeshes[i]->mVertices[aScene->mMeshes[i]->mFaces[j].mIndices[k]].z;
					std::cout <<"]"<< std::endl;
				}
			}
			for(int j = 0; j < AI_MAX_NUMBER_OF_COLOR_SETS; j++){
			
				std::cout << "aiScene->mMeshes["<< i <<"]->HasVertexColors["<< j <<"]: "<< aScene->mMeshes[i]->HasVertexColors(j) <<"\n"<<std::endl;
				if( aScene->mMeshes[i]->HasVertexColors(j)){
					for(int k = 0; k < aScene->mMeshes[i]->mNumVertices; k++){
						std::cout <<  aScene->mMeshes[i]->mColors[j][k].r << " - " <<  aScene->mMeshes[i]->mColors[j][k].g << " - "<<  aScene->mMeshes[i]->mColors[j][k].b<<std::endl;
					}
				}
			}
		}
		std::cout << "\n--------------------------\n"<<std::endl;
	}
	// ------------------------
	
	// Init Scene
	std::cout << "CREATION SCENE" <<std::endl;
	std::vector <Mesh> scene;
	if(aScene->HasMeshes()){
		if(aScene->HasMaterials()){
			aiMaterial *mat;
			for(int i = 0; i < aScene->mNumMeshes; i++){
				scene.push_back(Mesh(
					aScene->mMeshes[i],
					aScene->mMaterials[aScene->mMeshes[i]->mMaterialIndex]
				));
			}
		}
		else{
			for(int i = 0; i < aScene->mNumMeshes; i++){
				scene.push_back(Mesh(aScene->mMeshes[i]));
			}
		}
	}
	// ------------------------
	std::cout<< "CREATION SCENE FINI" << std::endl;
	// Application loop:
	bool done = false;
	
//Caméra etlumière directionnelle
	TrackballCamera camera;
    
    vec4 lightDir;
    vec4 lightPos; //A supprimer plus tard
    vec4 axeX; //A supprimer plus tard
    vec4 axeY; //A supprimer plus tard
    vec4 halfAxes; //A supprimer
    double x = 1;
    double y = 1;
    double z = 1;
//---------------------------------
	GLuint ubo = 0;
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, EllipsoidLight::numLights * sizeof(EllipsoidLight), &EllipsoidLight, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	GLuint binding_point_index = 2;
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, ubo);
    

	while(!done) {
		// Event loop:
		// Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
			switch( e.type ){
				case SDL_MOUSEMOTION:
					camera.rotateLeft((float) e.motion.xrel);
					camera.rotateUp((float) e.motion.yrel);
					break;
					
				case SDL_MOUSEBUTTONDOWN: 
					switch(e.button.button){
						case SDL_BUTTON_WHEELUP:
							camera.moveFront(-0.3);
						break;
						case SDL_BUTTON_WHEELDOWN:
							camera.moveFront(0.3);
						break;

					}
				break;
					
				case SDL_QUIT:
					done = true; // Leave the loop after this iteration
					break;

				default:
					break;
			}
        }
        
        if(windowManager.isKeyPressed(SDLK_z))
			camera.rotateUp(2);
        if(windowManager.isKeyPressed(SDLK_q))
			camera.rotateLeft(2);
        if(windowManager.isKeyPressed(SDLK_s))
			camera.rotateUp(-2);
        if(windowManager.isKeyPressed(SDLK_d))
			camera.rotateLeft(-2);
		if(windowManager.isKeyPressed(SDLK_r))
			x += 0.1;
		if(windowManager.isKeyPressed(SDLK_f))
			x -= 0.1;
		if(windowManager.isKeyPressed(SDLK_t))
			y += 0.1;
		if(windowManager.isKeyPressed(SDLK_g))
			y -= 0.1;
		if(windowManager.isKeyPressed(SDLK_y))
			z += 0.1;
		if(windowManager.isKeyPressed(SDLK_h))
			z -= 0.1;

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/
		 
		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		 
//Matrices de transformation pour vue caméra
		vectorProgram.m_Program.use();

		MVMatrix = camera.getViewMatrix();
		//MVMatrix = rotate(MVMatrix, windowManager.getTime(), vec3(0, 1, 0));
		glUniformMatrix4fv(vectorProgram.uMVMatrix, 1, GL_FALSE, value_ptr(MVMatrix));
		glUniformMatrix4fv(vectorProgram.uNormalMatrix, 1, GL_FALSE, value_ptr(transpose(inverse(MVMatrix))));
		glUniformMatrix4fv(vectorProgram.uMVPMatrix, 1, GL_FALSE, value_ptr(ProjMatrix * MVMatrix));
		
//Lumière directionnelle
		lightDir = camera.getViewMatrix() * vec4(1.0f, 1.0f, 1.0f, 0.f);
		
		lightPos = vec4(0.f, 2.f, 0.f, 1.f); //A supprimer plus tard
		axeX = vec4(1.f, 0.f, 0.f, 0.f); //A supprimer plus tard
		axeY = vec4(0.f, 1.f, 0.f, 0.f); //A supprimer plus tard
		
//Vecteurs de debug
		glUniform3f(vectorProgram.uColor, 1.f, 0, 0);
		float tStep = (M_PI) / (float)32;
		float sStep = (M_PI) / (float)32;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for(float t = -M_PI/2; t <= (M_PI/2)+.0001; t += tStep)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for(float s = -M_PI; s <= M_PI+.0001; s += sStep)
			{
				glVertex3f(x * cos(t) * cos(s)+0, y * cos(t) * sin(s) + 2, z * sin(t) + 0);
				glVertex3f(x * cos(t+tStep) * cos(s)+0, y * cos(t+tStep) * sin(s) + 2, z * sin(t+tStep) + 0);
			}
			glEnd();
		}
		glUniform3f(vectorProgram.uColor, 0, 1.f, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POINTS);
			glVertex3f(3, 0, 0);
		glEnd();
		glUniform3f(vectorProgram.uColor, 1.f, 0, 0);
		glBegin(GL_LINES);
			glVertex3f(0,0,0); glVertex3f(1.f,0.0,0.0);
		glEnd();
		
		glUniform3f(vectorProgram.uColor, 0, 1.f, 0); 
		glBegin(GL_LINES);
			glVertex3f(0,0,0); glVertex3f(0.0,1.f,0.0);
		glEnd();
			
		glUniform3f(vectorProgram.uColor, 0, 0, 1.f);
		glBegin(GL_LINES);
			glVertex3f(0,0,0); glVertex3f(0.0,0.0,1.f);
		glEnd();
//----------------
		
		environmentProgram.m_Program.use();
		MVMatrix = scale(MVMatrix, vec3(1, 0.01, 1));
		glUniform1f(environmentProgram.uShininess, 60.f);
		glUniform3f(environmentProgram.uLightDir_vs, lightDir.x,  lightDir.y, lightDir.z);
		
		glUniformBlockBinding(environmentProgram, block_index, binding_point_index);
		glUniform3f(environmentProgram.uLightPos, lightPos.x,  lightPos.y, lightPos.z); //A supprimer plus tard
		glUniform3f(environmentProgram.uAxeX, axeX.x,  axeX.y, axeX.z); //A supprimer plus tard
		glUniform3f(environmentProgram.uAxeY, axeY.x,  axeY.y, axeY.z); //A supprimer plus tard
		halfAxes = vec4(x, y, z, 0.f); //A supprimer
		glUniform3f(environmentProgram.uHalfAxes, halfAxes.x, halfAxes.y, halfAxes.z); //A supprimer plus tard
		glUniform1i(environmentProgram.uNumLights, numLights);
		
		glUniform3f(environmentProgram.uLightIntensity,10.f, 10.f, 10.f);
		glUniformMatrix4fv(environmentProgram.uCamera, 1, GL_FALSE, value_ptr(camera.getViewMatrix()));
		glUniformMatrix4fv(environmentProgram.uMVMatrix, 1, GL_FALSE, value_ptr(MVMatrix));
		glUniformMatrix4fv(environmentProgram.uNormalMatrix, 1, GL_FALSE, value_ptr(transpose(inverse(MVMatrix))));
		glUniformMatrix4fv(environmentProgram.uMVPMatrix, 1, GL_FALSE, value_ptr(ProjMatrix * MVMatrix));
//-----------------------------------------
		
		for(auto it : scene) it.drawMesh();
		
		// Update the display
		windowManager.swapBuffers();
	}

	return EXIT_SUCCESS;
}

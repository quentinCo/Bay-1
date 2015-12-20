// Import lib C++
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// Import SDL
#include <SDL/SDL.h>

// Import glimac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

// Import GL
#include <GL/glew.h>
//#include <GL/glut.h>

// Import assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Import gtest
#include <gtest/gtest.h>

// Import
#include <libPerso/Scene.hpp>
#include <libPerso/Camera.hpp>

#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049


using namespace glimac;

int main(int argc, char** argv) {

	// Initialize SDL and open a window
	unsigned int windowWidth = 800;
	unsigned int windowHeight = 800;
	
	SDLWindowManager windowManager(windowWidth, windowHeight, "Bay-1");


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
	
	// Shader
	FilePath applicationPath(argv[0]);

	// Chargement des shaders
	Program program = loadProgram(applicationPath.dirPath() + "shaders/test.vs.glsl", applicationPath.dirPath() + "shaders/test.fs.glsl");
	program.use();


	// Verif existance fichier
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/nanosuit/nanosuit.obj";
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/borderland/Lilith/Lilith.obj";
	std::string pathFile = applicationPath.dirPath()+ "assets/models/borderland/Maya_obj/maya_3.obj";
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/forme_test_collor.obj";
	
// Init Scene
	std::cout << "CREATION SCENE" <<std::endl;

	Scene scene = Scene(pathFile.c_str());
// ------------------------

// Init Camera
	std::cout<< "CREATION SCENE FINI" << std::endl;
	
	glEnable(GL_DEPTH_TEST); 
	
	Camera camera = Camera();
// -----------------------
	
// Variable utiles pour la Camera
	bool mousePositionInit = false;
	glm::vec2 mousePosition = glm::vec2(0,0);
	// float hypotenus;
	
	float speedXY = 0.01;
	
	glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1.f,0.1f,100.f);
	glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0.f,0.f,-5.f));
// ------------------------------


/*
GLint total_mem_kb = 0;
glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, 
              &total_mem_kb);

GLint cur_avail_mem_kb = 0;
glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, 
              &cur_avail_mem_kb);
std::cout << "MEMOIR GPU => cur_avail_mem_kb / total_mem_kb : " << cur_avail_mem_kb << " / "<<total_mem_kb << std::endl;
*/

// Application loop:	
	bool loop = false;
	while(!loop) {
	// Traitement des events
		SDL_Event e;
				
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT){
				loop = true;
				break;
			}
			switch(e.type){
				case SDL_MOUSEMOTION:
					camera.rotateUp(-e.motion.yrel * (180.f/windowHeight));
					camera.rotateLeft(-e.motion.xrel * (180.f/windowWidth));
					break;

				case SDL_KEYDOWN:
					switch(e.key.keysym.sym){
						case SDLK_ESCAPE : 
							loop = true;
							break;
						default : break;
				}
				break;

				default:
				break;
			}		
		}
		
		// Gestion Deplacement (la touche reste enfoncé)
		Uint8 *keystate = SDL_GetKeyState(NULL);
		if ( keystate[SDLK_z]) camera.moveFront(speedXY);
		else if ( keystate[SDLK_s]) camera.moveFront(-speedXY);
		
		if ( keystate[SDLK_q]) camera.moveLeft(speedXY);
		else if ( keystate[SDLK_d]) camera.moveLeft(-speedXY);
		
		if ( keystate[SDLK_a]) camera.moveTop(speedXY);	// Monter
		else if ( keystate[SDLK_e]) camera.moveTop(-speedXY);	// Descendre
		
	// -------------------------------------------------------------------
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/
	 	
		//for(auto it : scene) it.drawMesh(program);

		glm::mat4 globalMVMatrix = camera.getViewMatrix();
		
		//std::cout << globalMVMatrix << std::endl;

		glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(globalMVMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
		glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(ProjMatrix * globalMVMatrix));

		// Dessin
		scene.drawScene(program);
		// ----------------------

		// Update the display
		windowManager.swapBuffers();
		/*
glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, 
              &total_mem_kb);

glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, 
              &cur_avail_mem_kb);
std::cout << "MEMOIR GPU => cur_avail_mem_kb / total_mem_kb : " << cur_avail_mem_kb << " / "<<total_mem_kb << std::endl;
		*/
	}

	return EXIT_SUCCESS;
}

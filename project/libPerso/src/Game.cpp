#include <libPerso/Game.hpp>

using namespace std;

Game * Game::instance = NULL;

Game::Game(string dir, string winName, uint32_t windowWidth, uint32_t windowHeight)
:windowManager(windowWidth, windowHeight, winName.c_str())
{
	// Initialisation du repertoire courrent.
	glimac::FilePath applicationPath(dir);
	currentDir = applicationPath.dirPath();
	
	// Initialisatioin du chemin pour les shaders.
	Program::setShadersDirectory(currentDir);
	std::cout << " dir : " << currentDir <<endl; 

	// Initialisation des propriètés OpenGL. 
	initOpenGLProperties();
	
	// Chargementde la liste de sites.
	initListeSite();
	
	// Chargement du premier site.
	player = Player(glm::vec3(0,0,0), glm::vec3(0,0,1), 0.05, 0.5);;
	initNewCurrentSite(siteHeader[firstSite]);
}

Game::~Game(){

	SDL_WM_GrabInput(SDL_GRAB_OFF);
	SDL_ShowCursor(SDL_ENABLE);

	delete instance;
}


Game* Game::getInstanceGame(string dir, string winN, uint32_t winW, uint32_t winH){

	if(instance == NULL) instance = new Game(dir, winN, winW, winH);
	return instance;
}


int Game::initOpenGLProperties(){
	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
	
	glEnable(GL_DEPTH_TEST);
/*
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
*/
		
	SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_ShowCursor(SDL_DISABLE);

	return 1;
}

int Game::initListeSite(){
	string path = currentDir + "/assets/config/config.json";
	FILE* fp = fopen(path.c_str(), "r");
	
	if(fp == NULL){
		std::cerr << "Fichier introuvable : " << currentDir << "/assets/config/config.json" << std::endl;
		return EXIT_FAILURE;
	}
	
	char readBuffer[256];
	
	rapidjson::FileReadStream bis(fp, readBuffer, sizeof(readBuffer));
	
	rapidjson::AutoUTFInputStream<unsigned, rapidjson::FileReadStream> eis(bis);  // wraps bis into eis
	
	rapidjson::Document doc;
	
	doc.ParseStream<0, rapidjson::AutoUTF<unsigned> >(eis); // This parses any UTF file into UTF-8 in memory
	fclose(fp);

	string directorySite = doc["directory"].GetString();

	const rapidjson::Value& docToLoad = doc["fileToLoad"];
	
	
	if(docToLoad.IsObject()){
		for (rapidjson::Value::ConstMemberIterator site = docToLoad.MemberBegin(); site != docToLoad.MemberEnd(); site++) {
 
 			if(firstSite == "") firstSite = site->name.GetString();

			std::string next[2];
			
			const rapidjson::Value& nextElement = site->value["next"];
			for(rapidjson::SizeType j = 0; j < nextElement.Size(); j++){
				next[j] = nextElement[j].GetString();
				//std::cout << "i : " << j << " --- > " << nextElement[j].GetString() << std::endl;
			}
			
			siteHeader.insert(std::pair<string,SceneHeader>(
				site->name.GetString(),
				SceneHeader(currentDir + "/assets/" + directorySite + "/" + site->value["path"].GetString(), next)
			));
		}
	}
	else{
		std::cerr << "Le fichier n'est conforme" << std::endl;
		return EXIT_FAILURE;
	}
	
	return 1;
	
}

void Game::initNewCurrentSite(const SceneHeader &scene){
	currentSite = Scene(scene.path, scene.next);
	
	player.setPosition(currentSite.getCameraPosition());
	cout << "scene.getPosition : " << currentSite.getCameraPosition() <<endl;
	cout << "player.getPosition : " << player.getPosition() <<endl;
	player.setFrontVector(currentSite.getCameraFront());
	
	cout << "scene.getCameraFront : " << currentSite.getCameraFront() <<endl;
	cout << "player.getFrontVector : " << player.getFrontVector() <<endl;
}

void Game::gamePlay(){
	cout << "PLAY" <<endl;
	loopPlay = false;
	while(!loopPlay) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Dessin
		glm::mat4 viewMatrix = player.getViewMatrix();
		//cout << "viewMatrix : " << viewMatrix <<endl;
		currentSite.drawScene(viewMatrix);

		
		// Traitement des events
		gameEvent();
		
		windowManager.swapBuffers();
	}
}

void Game::gameEvent(){
	//cout<<"EVENT GESTION" << endl;
	SDL_Event e;
	string next ="";			
	while(SDL_PollEvent(&e)){
		if(e.type == SDL_QUIT){
			loopPlay = true;
			break;
		}
		switch(e.type){
			case SDL_MOUSEMOTION:
				//cout << "MOUSE MOVE" << endl;
				player.playerRotate(e.motion);
				break;

			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
					case SDLK_RIGHT :
						next = currentSite.getNext(1);
						if(next != "") initNewCurrentSite(siteHeader[next]);
						break;
					case SDLK_LEFT :
						next = currentSite.getNext(0);
						if(next != "") initNewCurrentSite(siteHeader[next]);
						break;
					case SDLK_ESCAPE : 
						loopPlay = true;
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
	player.playerMove(keystate);

}





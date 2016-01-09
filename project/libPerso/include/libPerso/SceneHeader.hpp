#ifndef SCENE_HEADER_H
#define SCENE_HEADER_H

#include <iostream>
#include <cstdlib>
#include <cstring>
/*

	Structure permettant la sauvegarde des éléments nécéssaire à l'initialisation à l'initialisation des sites.

*/
struct SceneHeader{
	std::string path;
	std::string next[2];
	
	SceneHeader(){};
	
	SceneHeader(std::string p, std::string n[2]):path(p){
		next[0] = n[0];
		next[1] = n[1];
	};
	
	SceneHeader(const SceneHeader &s):path(s.path){
		next[0] = s.next[0];
		next[1] = s.next[1];
	};
	
	~SceneHeader(){};
};

#endif
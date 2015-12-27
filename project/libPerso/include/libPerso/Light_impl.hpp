#ifndef LIGHT_IMPL_H
#define LIGHT_IMPL_H

// Binding des lumières et envoie au programme
template<typename lightT>
void bindLights(const Program &prog, const lightT *lights){
	//std::cout << "Il y a combien de lumières Bébert ? " << lightT::numLights << std::endl; //Debug line
	//std::cout << "Il y a combien de lumières Bébert ? " << lights[0].position << std::endl; //Debug line
	//std::cout << "uniform name ? " << (lightT::uniformName + "_nb").c_str() << std::endl; //Debug line
	//std::cout << "Taille " << lightT::numLights * sizeof(float)*3*4 << " Taille " << lightT::numLights * sizeof(lightT) << std::endl; //Debug line
	
	// On obtient l'emplacement du bloc uniforme
    GLuint Lights_binding = lightT::numLights;
    GLint uniform_block_index = glGetUniformBlockIndex(prog.getGLId(), lightT::uniformName.c_str());
    // On bind le bloc
    glUniformBlockBinding(prog.getGLId(), uniform_block_index, Lights_binding);
    
    // On créé le buffer d'uniforme
    GLuint ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, lightT::numLights * sizeof(lightT), lights, GL_STREAM_DRAW); // On envoie les données des lumières au buffer
    
	glBindBufferRange(GL_UNIFORM_BUFFER, Lights_binding, ubo, 0, sizeof(lightT) * lightT::numLights);
	
	glUniform1i(glGetUniformLocation(prog.getGLId(), (lightT::uniformName + "_nb").c_str()), lightT::numLights); // On envoie le nombre de lumières au programme
}

//--------------------------

#endif

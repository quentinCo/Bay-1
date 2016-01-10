#ifndef LIGHT_IMPL_H
#define LIGHT_IMPL_H

// Binding des lumières et envoie au programme
template<typename lightT>

class LightBuffer{
	private : 
		GLuint ubo;
		GLenum target;
		//int size;
		static std::map<GLuint, unsigned int> occurenceCounter;
		
	public :
	
		LightBuffer(){};
		
		LightBuffer(const GLenum t):target(t){
			// On créé le buffer d'uniforme
			glGenBuffers(1, &ubo);
			
			occurenceCounter[ubo]++;
		}
		
		LightBuffer(const LightBuffer<lightT> &l): ubo(l.ubo), target(l.target){
			occurenceCounter[ubo]++;
		}
		
		LightBuffer& operator =(LightBuffer<lightT>& lvalue){
			ubo = lvalue.ubo;
			target = lvalue.target;
			
			occurenceCounter[ubo]++;
			
			return *this;
		}
		
		LightBuffer& operator =(LightBuffer<lightT>&& rvalue){
			ubo = rvalue.ubo;
			target = rvalue.target;
			
			rvalue.ubo = 0;
			
			return *this;
		}
		
		~LightBuffer(){
			occurenceCounter[ubo]--;
			if(occurenceCounter[ubo] == 0){ glDeleteBuffers(1, &ubo);}
		}
		
		void bindLights(const Program &prog, const lightT *lights){
			// On obtient l'emplacement du bloc uniforme
			GLuint Lights_binding = lightT::bindingIndex;
			GLint uniform_block_index = glGetUniformBlockIndex(prog.getGLId(), lightT::uniformName.c_str());
			
			// On bind le bloc
			glUniformBlockBinding(prog.getGLId(), uniform_block_index, Lights_binding);

			glBindBuffer(target, ubo);
			glBufferData(target, lightT::numLights * sizeof(lightT), lights, GL_STREAM_DRAW); // On envoie les données des lumières au buffer

			glBindBufferRange(target, Lights_binding, ubo, 0, sizeof(lightT) * lightT::numLights);

			glUniform1i(glGetUniformLocation(prog.getGLId(), (lightT::uniformName + "_nb").c_str()), lightT::numLights); // On envoie le nombre de lumières au programme			
		}
		
		void unbindLights(){
			glBindBuffer(target, 0);
		}

};
//--------------------------

template<typename lightT>
std::map<GLuint, unsigned int>  LightBuffer<lightT>::occurenceCounter;

#endif

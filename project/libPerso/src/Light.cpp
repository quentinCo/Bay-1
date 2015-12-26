#include <libPerso/Light.hpp>

using namespace glm;

// Constructeurs
EllipsoidLight::EllipsoidLight(const vec4 &pos, const vec4 &halfA, const vec4 &lightI)
: position(pos), halfAxes(halfA), lightIntensity(lightI)
{
	numLights++;
}

EllipsoidLight::EllipsoidLight(const EllipsoidLight &l)
: position(l.position), halfAxes(l.halfAxes), lightIntensity(l.lightIntensity)
{
	numLights++;
}
// ---------------------

// Destructeur
EllipsoidLight::~EllipsoidLight(){
	numLights--;
}
// ---------------------

std::ostream & operator<< (std::ostream & os, const EllipsoidLight &light){
	os << "Position : [" << light.position.x << ", " << light.position.y << ", " << light.position.z << "]\n";
	os << "HalfAxes : [" << light.halfAxes.x << ", " << light.halfAxes.y << ", " << light.halfAxes.z << "]\n\n";
	os << "LightIntensity : [" << light.lightIntensity.x << ", " << light.lightIntensity.y << ", " << light.lightIntensity.z << "]\n\n";
	return os;
}

// Uniform value 
/*void EllipsoidLight::uEllipsoidLights(const Program &prog){
	glUniform3fv(glGetUniformLocation(prog.getGLId(), "uEllipsoidLights.diffuseColor"),1, value_ptr(material.diffuseColor));
	glUniform3fv(glGetUniformLocation(prog.getGLId(), "uEllipsoidLights.ambientColor"),1, value_ptr(material.ambientColor));
	glUniform3fv(glGetUniformLocation(prog.getGLId(), "uEllipsoidLights.specularColor"),1, value_ptr(material.specularColor));
	glUniform3fv(glGetUniformLocation(prog.getGLId(), "uMaterial.emissionColor"),1, value_ptr(material.emissionColor));
	
	glUniform1f(glGetUniformLocation(prog.getGLId(), "uMaterial.shininess"), material.shininess);
	glUniform1f(glGetUniformLocation(prog.getGLId(), "uMaterial.opacity"), material.opacity);
}*/
// ---------------------

// Bind lights 
void bindLights(const Program &prog, const EllipsoidLight *lights){
	//std::cout << "Lights number " << EllipsoidLight::numLights << std::endl; //Debug line
	// obtain location of the uniform block
    GLuint Lights_binding = 0;
    GLint uniform_block_index = glGetUniformBlockIndex(prog.getGLId(), "uAllEllipsoidLigths");
    // assign the block binding
    glUniformBlockBinding(prog.getGLId(), uniform_block_index, Lights_binding);
    
    // create uniform buffer
    GLuint ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, EllipsoidLight::numLights*sizeof(float)*3*4, lights, GL_STREAM_DRAW);
    
    //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float)*4, lights);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBindBufferRange(GL_UNIFORM_BUFFER, Lights_binding, ubo, 0, sizeof(float)*EllipsoidLight::numLights*3*4);
}
// ---------------------

// Place lights
void setLights(){
	GLuint Lights_binding = 0;
	GLuint ubo;
    glGenBuffers(1, &ubo);
	
}
// ---------------------

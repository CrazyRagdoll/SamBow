#pragma once

#include <string>
#include <GL/glew.h>

//OPENGL SHADING LANGUAGE
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	//Read our vertex and fragment shaders and compile them
	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	//Link the shaders to the program
	void linkShaders();

	void addAttribute(const std::string& attributeName);

	void use();
	void unuse();

private:

	int _numAttributes;

	void compileShader(const std::string& filePath, GLuint id);

	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};


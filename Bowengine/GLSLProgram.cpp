#include "GLSLProgram.h"
#include "Errors.h"

#include <vector>

#include <fstream>

GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{

}


GLSLProgram::~GLSLProgram()
{
}

//Read our vertex and fragment shaders and compile them
void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	//Create the vertex shader object, and store its ID
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("Vertex shader failed to be created!");
	}

	//Create the fragment shader object, and store its ID
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		fatalError("Fragment shader failed to be created!");
	}

	//compile each shader
	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

//Link the shaders to the program
void GLSLProgram::linkShaders() {
	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the prgram anymore
		glDeleteProgram(_programID);
		//Don't leak shaders either
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		//Print out the error log
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shaders failed to link!");

	}

	//Detach shaders after a successful link
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	//Delete shaders after a successful link
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

//Adds an attribute to our shader, should be called between compiling and linking
void GLSLProgram::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

//Returns a uniform location to GLunit
GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + uniformName + " not found in shader!");
	}
	return location;
}

//Enable the shader and all of its attributes
void GLSLProgram::use() {
	glUseProgram(_programID);
	//Enable all the attrivutes we added with addAttribute
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

//Compile the shader files
void GLSLProgram::compileShader(const std::string& filePath, GLuint id) {
	//Get the program object
	_programID = glCreateProgram();

	//Open the file
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		perror(filePath.c_str());
		fatalError("Failed to open " + filePath);
	}

	//File contents stores all the text in the file
	std::string fileContents = "";
	//Line is used to grab each line of the file
	std::string line;

	//Get all the lines in the file and add it to the contents
	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}

	vertexFile.close();

	//Get a pointer to our file contents c string
	const char* contentsPtr = fileContents.c_str();
	//tell opengl that we want to use fileContents as teh contents of the shader file
	glShaderSource(id, 1, &contentsPtr, nullptr);

	//compile the shader
	glCompileShader(id);

	//Check for errors
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//The MaxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		//Exit with failure
		glDeleteShader(id);

		//Print out the error log
		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader " + filePath + " failed to compile");
	}
}
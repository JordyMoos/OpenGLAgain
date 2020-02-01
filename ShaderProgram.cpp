#include "ShaderProgram.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	unsigned int vertex = createShader(vertexPath, GL_VERTEX_SHADER);
	unsigned int fragment = createShader(fragmentPath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	guardLinkErrors();
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


unsigned int ShaderProgram::createShader(const char* path, GLenum shaderType) const
{
	const char* code;

	try
	{
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		shaderFile.open(path);
		std::stringstream stream;
		stream << shaderFile.rdbuf();
		code = stream.str().c_str();
		shaderFile.close();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "Error: could not read shader: " << path << std::endl;
		throw std::runtime_error("ERROR: could not read shader");
	}

	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	guardCompileErrors(shader);

	return shader;
}


void ShaderProgram::guardCompileErrors(const unsigned int shader) const
{
	int success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if ( ! success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error: shader compilation failed" << std::endl;
		throw std::runtime_error("Error: shader compilation failed");
	}
}


void ShaderProgram::guardLinkErrors() const
{
	int success;

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if ( ! success)
	{
		char infoLog[512];
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "Error: shader linking failed" << std::endl;
		throw std::runtime_error("Error: shader linking failed");
	}
}

#pragma once

#include <glad/glad.h>

#include <string>

class ShaderProgram
{
protected:
	unsigned int id;

public:
	ShaderProgram(const char* vertexPath, const char* fragmentPath);

	void use()
	{
		glUseProgram(id);
	}

	// uniform functions
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

protected:
	unsigned int createShader(const char* path, GLenum shaderType) const;
	void guardCompileErrors(const unsigned int shader) const;
	void guardLinkErrors() const;
};

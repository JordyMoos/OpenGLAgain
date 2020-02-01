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
	void set1b(const std::string& name, bool b1) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)b1);
	}

	void set1i(const std::string& name, int i1) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), i1);
	}

	void set1f(const std::string& name, float f1) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), f1);
	}

	void set4f(const std::string& name, float f1, float f2, float f3, float f4) const
	{
		glUniform4f(glGetUniformLocation(id, name.c_str()), f1, f2, f3, f4);
	}

protected:
	unsigned int createShader(const char* path, GLenum shaderType) const;
	void guardCompileErrors(const unsigned int shader) const;
	void guardLinkErrors() const;
};

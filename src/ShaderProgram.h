#pragma once

#include <glad/glad.h>
#include <string>
#include <optional>
#include <optional>

class ShaderProgram
{
protected:
	unsigned int id;

public:
	ShaderProgram(const char* vertexPath, const char* fragmentPath, std::optional<const char*> geometryPath = std::nullopt);

	void use()
	{
		glUseProgram(id);
	}

	// uniform functions
	void set1b(const std::string& name, bool b1)
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)b1);
	}

	void set1i(const std::string& name, int i1)
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), i1);
	}

	void set1f(const std::string& name, float f1)
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), f1);
	}

	void set4f(const std::string& name, float f1, float f2, float f3, float f4)
	{
		glUniform4f(glGetUniformLocation(id, name.c_str()), f1, f2, f3, f4);
	}

	void setMatrix4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value)
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), count, transpose, value);
	}

protected:
	unsigned int createShader(const char* path, GLenum shaderType) const;
	void guardCompileErrors(const unsigned int shader) const;
	void guardLinkErrors() const;
};

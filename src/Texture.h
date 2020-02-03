#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>

class Texture
{
protected:
	unsigned int id;

public:
	Texture(const char* path);
	Texture(std::vector<std::string> faces);

	void bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void seti(GLenum pname, GLint param)
	{
		glTexParameteri(GL_TEXTURE_2D, pname, param);
	}
};

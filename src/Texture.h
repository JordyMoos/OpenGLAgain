#pragma once

#include <glad/glad.h>

class Texture
{
protected:
	unsigned int id;
	int width;
	int height;
	int nrChannels;

public:
	Texture(const char* path, GLint internalFormat, GLenum format);


	void bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void seti(GLenum pname, GLint param)
	{
		glTexParameteri(GL_TEXTURE_2D, pname, param);
	}
};


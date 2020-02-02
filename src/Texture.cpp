#include "Texture.h"
#include <iostream>

#include "stb_image.h"

Texture::Texture(const char* path, GLint internalFormat, GLenum format) : id(0), width(0), height(0), nrChannels(0)
{
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if ( ! data)
	{
		std::cout << "Error: could not load texture " << path << std::endl;
		throw new std::runtime_error("Error: Could not load texture");
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	seti(GL_TEXTURE_WRAP_S, GL_REPEAT);
	seti(GL_TEXTURE_WRAP_T, GL_REPEAT);
	seti(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	seti(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

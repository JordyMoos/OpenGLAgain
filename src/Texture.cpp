#include "Texture.h"
#include <iostream>

#include "stb_image.h"

Texture::Texture(const char* path) : id(0)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if ( ! data)
	{
		std::cout << "Error: could not load texture " << path << std::endl;
		throw new std::runtime_error("Error: Could not load texture");
	}

	GLenum format;
	if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	else
		format = GL_RED;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	seti(GL_TEXTURE_WRAP_S, GL_REPEAT);
	seti(GL_TEXTURE_WRAP_T, GL_REPEAT);
	seti(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	seti(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

Texture::Texture(std::vector<std::string> faces) : id(0)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	GLenum format;
	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (!data)
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			throw new std::runtime_error("Error: Could not load texture for cubemap");
		}

		if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		else
			format = GL_RED;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}



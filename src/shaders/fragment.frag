#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 textureCoordinate;

uniform sampler2D aTexture;

void main()
{
	FragColor = texture(aTexture, textureCoordinate) * vec4(color, 1.0);
}
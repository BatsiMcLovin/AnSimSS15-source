#ifndef __CVK_TEXTURE_H
#define __CVK_TEXTURE_H

#include "CVK_Defs.h"

namespace CVK
{

class Texture
{
public:
	Texture( char *fileName);
	Texture( int width, int height, int bytesPerPixel, unsigned char *data);
	Texture( GLuint texture);
	~Texture();

	bool load( char *fileName);
	void bind();

	void setTexture( GLuint texture);
	void setTexture( int width, int height, int bytesPerPixel, unsigned char *data);
	unsigned int getTexture();
	glm::vec3 getValue( glm::vec2 tcoord);

private:
	void createTexture();

	unsigned int m_textureID;
	int m_width, m_height;

	unsigned char *m_data; //keep copy e.g. for CPU ray tracing
	int m_bytesPerPixel;
};

};

#endif /*__CVK_TEXTURE_H*/

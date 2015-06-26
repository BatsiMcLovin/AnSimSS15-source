#ifndef __CVK_AS_SHADER_SPACE_H
#define __CVK_AS_SHADER_SPACE_H

#include "CVK_2/CVK_ShaderMinimal.h"

namespace CVK
{

class ShaderSpace : public CVK::ShaderMinimal
{
public:
	ShaderSpace(GLuint shader_mask, const char** shaderPaths);

	void update();
	void update(CVK::Node* node);


private:

	GLuint m_colorID;
	glm::vec3 m_color;

	GLuint m_useColorTexture, m_colorTextureID;
};

};

#endif /* __CVK_AS_SHADER_SPACE_H */


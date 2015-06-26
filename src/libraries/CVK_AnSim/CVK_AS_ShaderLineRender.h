#ifndef __CVK_AS_SHADER_LINE_RENDER_H
#define __CVK_AS_SHADER_LINE_RENDER_H

#include "CVK_2/CVK_ShaderMinimal.h"

namespace CVK
{

class ShaderLineRender : public CVK::ShaderMinimal
{
public:
	ShaderLineRender(GLuint shader_mask, const char** shaderPaths);

	void update();
	void update(glm::vec4& color);

private:
	GLuint m_colorID;
};

};

#endif /* __CVK_AS_SHADER_LINE_RENDER_H */


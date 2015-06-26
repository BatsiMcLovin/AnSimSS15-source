#include "CVK_AS_ShaderLineRender.h"

CVK::ShaderLineRender::ShaderLineRender(GLuint shader_mask, const char** shaderPaths)
	: CVK::ShaderMinimal(shader_mask, shaderPaths)
{
	m_colorID = glGetUniformLocation(m_ProgramID, "color");
}

void CVK::ShaderLineRender::update()
{
	CVK::ShaderMinimal::update();
	glUniform4fv(m_colorID, 1, glm::value_ptr(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
}

void CVK::ShaderLineRender::update(glm::vec4& color)
{
	updateModelMatrix(glm::mat4(1.0f));
	glUniform4fv(m_colorID, 1, glm::value_ptr(color));
}




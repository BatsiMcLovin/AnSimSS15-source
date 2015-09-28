#include "ShaderSkybox.h"

ShaderSkybox::ShaderSkybox( GLuint shader_mask, const char** shaderPaths) : CVK::ShaderMinimal(shader_mask, shaderPaths)
{	
	m_colorTextureID = glGetUniformLocation( m_ProgramID, "colortexture"); 
}

void ShaderSkybox::update()
{
    CVK::ShaderMinimal::update();
	glUniform1i(m_colorTextureID, 0);
	glActiveTexture(GL_TEXTURE0);
}


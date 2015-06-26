#include "CVK_AS_ShaderSpace.h"

CVK::ShaderSpace::ShaderSpace(GLuint shader_mask, const char** shaderPaths)
	: CVK::ShaderMinimal(shader_mask, shaderPaths)
{	
	//Material
	m_colorID = glGetUniformLocation(m_ProgramID, "color");
	m_color = glm::vec3(0.0,1.0,0.0);

	//Textures
	m_useColorTexture = glGetUniformLocation( m_ProgramID, "useColorTexture");
	m_colorTextureID = glGetUniformLocation( m_ProgramID, "colorTexture");
}

void CVK::ShaderSpace::update()
{
	CVK::ShaderMinimal::update();
}

void CVK::ShaderSpace::update(CVK::Node* node)
{
	
	if(node->hasMaterial())
	{
		CVK::Material* mat = node->getMaterial();
		CVK::Texture *color_texture;
		glUniform3fv(m_colorID, 1, glm::value_ptr( *mat->getdiffColor()));

		bool colorTexture = mat->hasTexture(COLOR_TEXTURE);
		glUniform1i(m_useColorTexture, colorTexture);

		if (colorTexture)
		{	
			//TODO: COLOR_TEXTURE_UNIT
			glUniform1i( m_colorTextureID, 0);

			glActiveTexture(COLOR_TEXTURE_UNIT);
			color_texture = mat->getTexture(COLOR_TEXTURE);
			color_texture->bind();
		}
	}
}




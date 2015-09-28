#ifndef __SHADER_SKYBOX_H
#define __SHADER_SKYBOX_H

#include <CVK_2/CVK_Framework.h>

class ShaderSkybox : public CVK::ShaderMinimal
{
public:
	ShaderSkybox(GLuint shader_mask, const char** shaderPaths);
	virtual void update();

private:
	GLuint m_colorTextureID;

};


#endif /*__SHADER_SIMPLE_TEXTURE_H*/
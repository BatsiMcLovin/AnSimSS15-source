#ifndef __CVK_SHADERPHONG_H
#define __CVK_SHADERPHONG_H

#include "CVK_Defs.h"
#include "CVK_Camera.h"
#include "CVK_Light.h"
#include "CVK_Material.h"
#include "CVK_Geometry.h"
#include "CVK_ShaderMinimal.h"

namespace CVK
{

class ShaderPhong : public CVK::ShaderMinimal
{
public:
	ShaderPhong( GLuint shader_mask, const char** shaderPaths);
	void update( );
	void update( CVK::Node* node);

private:
	GLuint m_kdID, m_ksID, m_ktID;
	GLuint m_diffuseID, m_specularID, m_shininessID;
	GLuint m_lightambID;

	GLuint m_numLightsID;
	GLuint m_lightposID[MAX_LIGHTS], m_lightcolID[MAX_LIGHTS], m_lightsdirID[MAX_LIGHTS], m_lightsexpID[MAX_LIGHTS], m_lightscutID[MAX_LIGHTS];

	GLuint m_useColorTexture, m_colorTextureID;

	GLuint m_fogcolID, m_fogstartID, m_fogendID, m_fogdensID, m_fogmodeID;
};

};

#endif /*__CVK_SHADERPHONG_H*/

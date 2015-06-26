#ifndef __CVK_MATERIAL_H
#define __CVK_MATERIAL_H

#include "CVK_Defs.h"
#include "CVK_Texture.h"

namespace CVK
{
	enum TextureType
	{
		COLOR_TEXTURE,
		NORMAL_TEXTURE
	};

class Material 
{
public:
	Material( glm::vec3 diffuse, glm::vec3 specular, float shininess); 
	Material( float kd, glm::vec3 diffuse); 
	Material( float kd, glm::vec3 diffuse, float ks, glm::vec3 specular, float shininess); 
	Material( char *colorTexturePath, float kd);
	Material( GLuint colorTextureID, float kd);
	Material( char *colorTexturePath, float kd, float ks, glm::vec3 specular, float shininess);
	Material( GLuint colorTextureID, float kd, float ks, glm::vec3 specular, float shininess);
	~Material( );

	void init( float kd, glm::vec3 diffuse, float ks, glm::vec3 specular, float shininess);

	void setKd ( float kd);
	float getKd();
	void setKs ( float ks);
	float getKs();
	void setKt ( float kt);
	float getKt();

	void setdiffColor( glm::vec3 col); 
	glm::vec3* getdiffColor();

	void setspecColor( glm::vec3 col); 
	glm::vec3* getspecColor();

	void setShininess( float shininess); 
	float getShininess();

	void setIor ( float ior);
	float getIor();

	void setTexture( TextureType type, char *fileName);
	void setTexture( TextureType type, GLuint textureID);
	bool hasTexture( TextureType type);
	CVK::Texture* getTexture( TextureType type);


private:

	float m_kd, m_ks, m_kt;
	glm::vec3 m_diffColor;
	glm::vec3 m_specColor;
	float m_shininess;
	float m_ior; //index of refraction

	CVK::Texture* m_colorTexture;
	CVK::Texture* m_normalTexture;
};

};

#endif /* __CVK_MATERIAL_H */


#ifndef _SKYBOX_H
#define _SKYBOX_H

#include <CVK_2/CVK_Framework.h>
#include <CVK_2/CVK_Texture.h>

class Skybox {
    
public:
    
    /**
     * Constructor
     */
    Skybox(const float size);
    
    /**
     * Destructor
     */
    ~Skybox();
    
    /**
     * Render the skybox.
     */
    void render();
    
    inline GLint getTextureHandle(void){return m_textureHandle;}
    
private:
    
    CVK::Texture *m_texture;
    GLuint m_vaoHandle; // vao
    GLuint m_vboHandles[2]; // vbo handels (vertices and uv coordinates)
    GLuint m_textureHandle; // texture handle
    
};

#endif
#include "Skybox.h"


Skybox::Skybox(const float size)
{
    GLfloat vertices[] = {
        // Front face
        -size,-size,-size, size,-size,-size, size,size,-size,
        size,size,-size, -size,size,-size, -size,-size,-size,
        // Right face
        size,-size,-size, size,-size,size, size,size,size,
        size,size,size, size,size,-size, size,-size,-size,
        // Back face
        size,-size,size, -size,-size,size, -size,size,size,
        -size,size,size, size,size,size, size,-size,size,
        // Left face
        -size,-size,size, -size,-size,-size, -size,size,-size,
        -size,size,-size, -size,size,size, -size,-size,size,
        // Bottom face
        -size,-size,size, size,-size,size, size,-size,-size,
        size,-size,-size, -size,-size,-size, -size,-size,size,
        // Top Face
        -size,size,-size, size,size,-size, size,size,size,
        size,size,size, -size,size,size, -size,size,-size,
    };
    
    GLfloat uvCoordinates[] = {
        // Front face
        1.0f/4.0f,1.0f/3.0f, 2.0f/4.0f,1.0f/3.0f, 2.0f/4.0f,2.0f/3.0f,
        2.0f/4.0f,2.0f/3.0f, 1.0f/4.0f,2.0f/3.0f, 1.0f/4.0f,1.0f/3.0f,
        // Right face
        2.0f/4.0f,1.0f/3.0f, 3.0f/4.0f,1.0f/3.0f, 3.0f/4.0f,2.0f/3.0f,
        3.0f/4.0f,2.0f/3.0f, 2.0f/4.0f,2.0f/3.0f, 2.0f/4.0f,1.0f/3.0f,
        // Back face
        3.0f/4.0f,1.0f/3.0f, 1.0f,1.0f/3.0f, 1.0f,2.0f/3.0f,
        1.0f,2.0f/3.0f, 3.0f/4.0f,2.0f/3.0f, 3.0f/4.0f,1.0f/3.0f,
        // Left face
        0.0f,1.0f/3.0f, 1.0f/4.0f,1.0f/3.0f, 1.0f/4.0f,2.0f/3.0f,
        1.0f/4.0f,2.0f/3.0f, 0.0f,2.0f/3.0f, 0.0f,1.0f/3.0f,
        // Bottom face
        1.0f/4.0f,0.0f, 2.0f/4.0f,0.0f, 2.0f/4.0f,1.0f/3.0f,
        2.0f/4.0f,1.0f/3.0f, 1.0f/4.0f,1.0f/3.0f, 1.0f/4.0f,0.0f,
        // Top face
        1.0f/4.0f,2.0f/3.0f, 2.0f/4.0f,2.0f/3.0f, 2.0f/4.0f,1.0f,
        2.0f/4.0f,1.0f, 1.0f/4.0f,1.0f, 1.0f/4.0f,2.0f/3.0f
    };
    
    glGenVertexArrays(1, &m_vaoHandle);
    glBindVertexArray(m_vaoHandle);
    
    // we generate multiple buffers at a time
    glGenBuffers(2, m_vboHandles);
    
    // bind the first buffer and store geometry into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // uses the second buffer as the source for uv coordinates
    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoordinates), uvCoordinates, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    // unbind the VBO, we don't need it anymore
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // load a skybox texture
    m_texture = new CVK::Texture(RESOURCES_PATH "/skybox_space4.png");
}

Skybox::~Skybox()
{
    // cleanup vao, vbos and texture
    glDeleteVertexArrays(1, &m_vaoHandle);
    glDeleteBuffers(2, &m_vboHandles[0]);

    delete m_texture;
    
}

void Skybox::render()
{
    
    // bind the ID texture specified by the 2nd parameter
    m_texture->bind();
    glBindVertexArray(m_vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
}

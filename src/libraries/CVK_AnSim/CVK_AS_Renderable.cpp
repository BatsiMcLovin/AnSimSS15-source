#include "CVK_AS_Renderable.h"

CVK::Renderable::Renderable()
{
	m_color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	setupBuffers();
}

CVK::Renderable::~Renderable()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteVertexArrays(1, &m_vao);
}

void CVK::Renderable::setupBuffers()
{
	glGenBuffers(1, &m_vertexBuffer);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


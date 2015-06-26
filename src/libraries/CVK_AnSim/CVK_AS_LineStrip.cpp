#include "CVK_AS_LineStrip.h"

CVK::LineStrip::LineStrip()
{

}

CVK::LineStrip::~LineStrip()
{

}

void CVK::LineStrip::render(CVK::ShaderLineRender* shader)
{	
	glm::vec4 color = getColor();
	shader->update(color);

	glBindVertexArray(m_vao);

	glDrawArrays(GL_LINE_STRIP, 0, m_points.size());

	glBindVertexArray(0);
}

void CVK::LineStrip::setVertices()
{
	std::vector<glm::vec4> vertices;
	for (unsigned int i = 0; i < m_points.size(); i++)
	{
		vertices.push_back(glm::vec4(m_points[i], 1.0f));
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_points.size() * sizeof(glm::vec4), &vertices[0], GL_STATIC_DRAW);
}

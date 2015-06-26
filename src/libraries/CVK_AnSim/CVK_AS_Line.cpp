#include "CVK_AS_Line.h"

void CVK::drawLine(CVK::ShaderLineRender* shader, glm::vec3 start, glm::vec3 end, glm::vec4 color)
{
	Line l(start, end);
	l.setColor(color);
	l.render(shader);
}




CVK::Line::Line()
{
	mStart = glm::vec3(0.0f);
	mEnd = glm::vec3(0.0f);

	setVertices();
}

CVK::Line::Line(glm::vec3 start, glm::vec3 end)
{
	mStart = start;
	mEnd = end;

	setVertices();
}

CVK::Line::~Line()
{

}

void CVK::Line::render(CVK::ShaderLineRender* shader)
{	
	glm::vec4 color = getColor();
	shader->update(color);

	glBindVertexArray(m_vao);

	glDrawArrays(GL_LINES, 0, 2);

	glBindVertexArray(0);
}

void CVK::Line::setVertices()
{
	std::vector<glm::vec4> vertices;
	vertices.push_back(glm::vec4(mStart, 1.0f));
	vertices.push_back(glm::vec4(mEnd, 1.0f));
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4), &vertices[0], GL_STATIC_DRAW);
}


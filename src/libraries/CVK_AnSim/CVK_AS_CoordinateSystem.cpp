#include "CVK_AS_CoordinateSystem.h"

CVK::CoordinateSystem::CoordinateSystem(glm::vec3 center)
{
	m_center = center;
	m_xAxis = CVK::Line(m_center, m_center + glm::vec3(3.0f, 0.0f, 0.0f));
	m_xAxis.setColor(glm::vec4(1, 0, 0, 1));
	m_yAxis = CVK::Line(m_center, m_center + glm::vec3(0.0f, 3.0f, 0.0f));
	m_yAxis.setColor(glm::vec4(0, 1, 0, 1));
	m_zAxis = CVK::Line(m_center, m_center + glm::vec3(0.0f, 0.0f, 3.0f));
	m_zAxis.setColor(glm::vec4(0, 0, 1, 1));
}

CVK::CoordinateSystem::~CoordinateSystem()
{

}

void CVK::CoordinateSystem::render(CVK::ShaderLineRender* shader)
{
	CVK::drawLine(shader, m_xAxis.getStartPoint(), m_xAxis.getEndPoint(), m_xAxis.getColor());
	CVK::drawLine(shader, m_yAxis.getStartPoint(), m_yAxis.getEndPoint(), m_yAxis.getColor());
	CVK::drawLine(shader, m_zAxis.getStartPoint(), m_zAxis.getEndPoint(), m_zAxis.getColor());
}

void CVK::CoordinateSystem::setLines()
{
	m_xAxis.setStartPoint(m_center);
	m_yAxis.setStartPoint(m_center);
	m_zAxis.setStartPoint(m_center);

	m_xAxis.setEndPoint(m_center + glm::vec3(3.0f, 0.0f, 0.0f));
	m_yAxis.setEndPoint(m_center + glm::vec3(0.0f, 3.0f, 0.0f));
	m_zAxis.setEndPoint(m_center + glm::vec3(0.0f, 0.0f, 3.0f));
}

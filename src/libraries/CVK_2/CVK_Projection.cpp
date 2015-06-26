#include "CVK_Projection.h"

glm::mat4 *CVK::Projection::getProjMatrix( )
{
	return &m_perspective;
	
}
void CVK::Projection::setProjMatrix( glm::mat4 *projection)
{
	m_perspective = *projection;
}

void CVK::Projection::getNearFar( float *near, float *far)
{
	*near = m_znear;
	*far = m_zfar;
}

float CVK::Projection::getNear()
{
	return m_znear;
}
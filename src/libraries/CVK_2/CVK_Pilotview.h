#ifndef __CVK_PILOTVIEW_H
#define __CVK_PILOTVIEW_H

#include "CVK_Camera.h"
#include "CVK_Perspective.h"

namespace CVK
{

class Pilotview : public CVK::Camera
{
public:
	Pilotview( int width, int height, CVK::Projection *projection);
	Pilotview( int width, int height);
	~Pilotview();

	void update( GLFWwindow *window);
	void setCamPos( glm::vec3 *campos);
	void setLookAt( glm::vec3 *position, glm::vec3 *center);
	void setUpvector( glm::vec3 *up);

private:
	glm::vec3 m_cameraPos, m_direction, m_up;

	float m_oldX, m_oldY;
	float m_step, m_sensitivity;
	float m_speed;
	float m_theta, m_phi;
};

};

#endif /* __CVK_PILOTVIEW_H */

// Cone along y-axis, origin in base midpoint

#ifndef __CVK_CONE_H
#define __CVK_CONE_H

#include "CVK_Defs.h"
#include "CVK_Geometry.h"

namespace CVK
{

class Cone : public CVK::Geometry
{
public:
	Cone();
	Cone( float baseradius, float apexradius, float height, int resolution);
	Cone( glm::vec3 basepoint, glm::vec3 apexpoint, float baseradius, float apexradius, int resolution);
	~Cone();

	glm::vec3 *getBasepoint();
	glm::vec3 *getApexpoint();
	glm::vec3 *get_u();
	glm::vec3 *get_v();
	glm::vec3 *get_w();
	float getBaseradius();
	float getApexradius();
	float getSlope();

private:
	void create();

	glm::vec3 m_basepoint, m_apexpoint;
	glm::vec3 m_u, m_v, m_w;
	float m_baseradius, m_apexradius, m_height, m_slope;
	int m_resolution;
};

};

#endif /* __CVK_CONE_H */


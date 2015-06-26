#ifndef __CVK_AS_COORDINATE_SYSTEM_H
#define __CVK_AS_COORDINATE_SYSTEM_H

#include "glm/glm.hpp"
#include "CVK_AS_Line.h"

namespace CVK
{

class CoordinateSystem
{
public:

	CoordinateSystem(glm::vec3 center);
	~CoordinateSystem();

	void render(CVK::ShaderLineRender* shader);

	inline void setCenterPoint(glm::vec3 center) { m_center = center; setLines(); }
	inline glm::vec3 getCenterPoint() { return m_center; }

	void setLines();

private:
	glm::vec3 m_center;

	CVK::Line m_xAxis, m_yAxis, m_zAxis;
};

};

#endif /* __CVK_AS_COORDINATE_SYSTEM_H */


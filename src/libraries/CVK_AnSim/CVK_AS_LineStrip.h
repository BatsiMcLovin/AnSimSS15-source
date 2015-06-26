#ifndef __CVK_AS_LINE_STRIP_H
#define __CVK_AS_LINE_STRIP_H

#include <vector>
#include "glm/glm.hpp"

#include "CVK_AS_Renderable.h"

namespace CVK
{

class LineStrip : public Renderable
{
public:
	LineStrip();
	~LineStrip();

	void render(CVK::ShaderLineRender* shader);

	inline void addPoint(glm::vec3 point) { m_points.push_back(point); setVertices(); }
private:
	std::vector<glm::vec3> m_points;

	void setVertices();
};

};

#endif /* __CVK_AS_LINE_STRIP_H */


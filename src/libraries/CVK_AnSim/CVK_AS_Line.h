#ifndef __CVK_AS_LINE_H
#define __CVK_AS_LINE_H

#include "glm/glm.hpp"

#include <CVK_2/CVK_Defs.h>
#include "CVK_AS_Renderable.h"

namespace CVK
{

	void drawLine(CVK::ShaderLineRender* shader, glm::vec3 start, glm::vec3 end, glm::vec4 color = glm::vec4(0, 1, 0, 1));

class Line : public Renderable
{
public:
	Line();
	Line(glm::vec3 start, glm::vec3 end);
	virtual ~Line();

	void render(CVK::ShaderLineRender* shader);

	inline void setStartPoint(glm::vec3 start) { mStart = start; setVertices(); }
	inline glm::vec3 getStartPoint() { return mStart; }

	inline void setEndPoint(glm::vec3 end) { mEnd = end; setVertices(); }
	inline glm::vec3 getEndPoint() { return mEnd; }

private:
	glm::vec3 mStart, mEnd;

	void setVertices();
};

};

#endif /* __CVK_AS_LINE_H */


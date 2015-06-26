#ifndef __CVK_AS_RENDERABLE_H
#define __CVK_AS_RENDERABLE_H

#include <CVK_2/CVK_Defs.h>
#include "glm/glm.hpp"

#include "CVK_AS_ShaderLineRender.h"

namespace CVK
{

class Renderable
{
public:
	Renderable();
	virtual ~Renderable();

	virtual void render(CVK::ShaderLineRender* shader) = 0;

	inline void setColor(glm::vec3 color) { m_color = glm::vec4(color, 1.0f); }
	inline void setColor(glm::vec4 color) { m_color = color; }
	inline glm::vec4 getColor() { return m_color; }

protected:
	GLuint m_vertexBuffer, m_vao;

private:
	glm::vec4 m_color;
	void setupBuffers();
};

};

#endif /* __CVK_AS_RENDERABLE_H */


#ifndef __CVK_TRIANGLE_H
#define __CVK_TRIANGLE_H

#include "CVK_Defs.h"
#include "CVK_Geometry.h"

namespace CVK
{

class Triangle : public CVK::Geometry
{
public:
	Triangle();
	Triangle( glm::vec3 a, glm::vec3 b, glm::vec3 c);
	Triangle( glm::vec3 a, glm::vec3 b, glm::vec3 c,  glm::vec3 na, glm::vec3 nb, glm::vec3 nc);
	Triangle( glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec2 tca, glm::vec2 tcb, glm::vec2 tcc);
	Triangle( glm::vec3 a, glm::vec3 b, glm::vec3 c,  glm::vec3 na, glm::vec3 nb, glm::vec3 nc, glm::vec2 tca, glm::vec2 tcb, glm::vec2 tcc);

	~Triangle();

	void set_Points( glm::vec3 a, glm::vec3 b, glm::vec3 c);
	void get_Points( glm::vec3 *a, glm::vec3 *b, glm::vec3 *c);

	void set_Normal( glm::vec3 n);
	void get_Normal( glm::vec3 *n);

	void set_Normals( glm::vec3 na, glm::vec3 nb, glm::vec3 nc);
	void get_Normals( glm::vec3 *na, glm::vec3 *nb, glm::vec3 *nc);

	void set_Tcoords( glm::vec2 tca, glm::vec2 tcb, glm::vec2 tcc);
	void get_Tcoords( glm::vec2 *tca, glm::vec2 *tcb, glm::vec2 *tcc);

private:
	void create( glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec2 tca, glm::vec2 tcb, glm::vec2 tcc);
	void create( glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 na, glm::vec3 nb, glm::vec3 nc, glm::vec2 tca, glm::vec2 tcb, glm::vec2 tcc);

};

};

#endif /* __CVK_TRIANGLE_H */


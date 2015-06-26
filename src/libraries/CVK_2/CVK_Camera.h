#ifndef __CVK_CAMERA_H
#define __CVK_CAMERA_H

#include "CVK_Defs.h"
#include "CVK_Projection.h"

namespace CVK
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		virtual void update( GLFWwindow* window) = 0;

		glm::mat4 *getView();
		void getView( glm::vec3 *x, glm::vec3 *y, glm::vec3 *z, glm::vec3 *pos);
		void setView( glm::mat4 *view);
		void setWidthHeight( int width, int height);
		void getWidthHeight( int *width, int *height);

		void lookAt( glm::vec3 position, glm::vec3 center, glm::vec3 up);
		void setProjection( CVK::Projection *projection);
		CVK::Projection *getProjection();

	protected:
		int m_width, m_height;
		glm::mat4 m_viewmatrix;
		CVK::Projection *m_projection;
	};
};

#endif /* __CVK_CAMERA_H */

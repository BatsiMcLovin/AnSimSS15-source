#ifndef __CVK_ORTHO_H
#define __CVK_ORTHO_H

#include "CVK_Defs.h"
#include "CVK_Projection.h"

namespace CVK
{
	class Ortho : public CVK::Projection
	{
	public:
		Ortho( float ratio);
		Ortho( float left, float right, float bottom, float top, float near, float far);
		~Ortho();

		void setOrtho( float left, float right, float bottom, float top, float near, float far);
		void setNearFar( float near, float far);
		void updateRatio( float ratio);

	protected:
		float m_left, m_right, m_bottom, m_top;
	};
};

#endif /* __CVK_ORTHO_H */

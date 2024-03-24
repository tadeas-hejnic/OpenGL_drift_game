//----------------------------------------------------------------------------------------
/**
 * \file       Elipse.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Elipse curve
 *
*/
//----------------------------------------------------------------------------------------

#ifndef _ELIPSE_H_
#define _ELIPSE_H_


#pragma once
#include "pgr.h"


class Elipse {
	glm::vec3 m_center;		///< Center position.
	glm::vec2 m_size;		///< Size.

	float prev_val_cos;		///< Previous value - used for correct rotations.
public:
	/// Constructor.
    /**
      Sets the given values.

      \param[in] center	    Center point of the elipse.
      \param[in] size       Vector of x and y size.
    */
	Elipse(glm::vec3 center, glm::vec2 size) : m_center(center), m_size(size) {}

	/// Position getter
	/**
      Returns the position on the elipse based on given time.

      \param[in] time		Current time.
    */
	glm::vec3 getPosition(float time);

	/// Direction getter
	/**
      Returns the direction on the elipse based on given time.

      \param[in] time		Current time.
    */
	glm::vec3 getDirection(float time);

	/// Angle getter
	/**
      Returns the view angle of the object on the elipse based on given time.

      \param[in] time		Current time.
    */
	float getAngle(float time);
};

#endif // _ELIPSE_H_

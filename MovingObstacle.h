//----------------------------------------------------------------------------------------
/**
 * \file       MovingObstacle.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Moving obstacle object
 *
*/
//----------------------------------------------------------------------------------------

#ifndef _MOVING_OBSTACLE_H_
#define _MOVING_OBSTACLE_H_

#pragma once
#include "Object.h"
#include "Elipse.h"


class MovingObstacle : public ObjectInstance {
	float currentTime;		///< Current time.
	float viewAngle;		///< View angle.
	float startAngle;		///< Starting view angle.
	glm::vec3 position;		///< Obstacle position.
	glm::vec3 direction;	///< Obstacle direction.
	glm::vec3 startPos;		///< Obstacle starting position.
	float size;				///< Obstacle size.

	Elipse* elipse;			///< Elipse curve.
public:
	/// Constructor.
    /**
      Sets the default values and calls the function for loading geometry from prepared C array.

      \param[in] elapsedTime    Elapsed time.
      \param[in] shdrPrg       	Pointer to shader for this obstacle object.
      \param[in] pos  			Obstacle position.
      \param[in] file_name  	Model file name.
    */
	MovingObstacle(float elapsedTime, CommonShader * shdrPrg, glm::vec3 pos, std::string file_name);

	void update(const float elapsedTime, const glm::mat4* parentModelMatrix) override;
	void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
};

#endif // _MOVING_OBSTACLE_H_

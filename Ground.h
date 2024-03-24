//----------------------------------------------------------------------------------------
/**
 * \file       Ground.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Ground object
*/
//----------------------------------------------------------------------------------------

#ifndef _GROUND_H_
#define _GROUND_H_


#pragma once
#include "Object.h"

class Ground : public ObjectInstance {
	glm::vec3 position;		///< Ground position.
	float size;				///< Ground size.

public:
	/// Constructor.
    /**
      Sets the variables to default values. Calls the method for loading geometry.

      \param[in] shdrPrg        Pointer to shader for this object.
    */
	Ground(ShaderProgram* shdrPrg = nullptr);

    /// Draw.
    /**
      Sets the uniforms and draw the object.

      \param[in] viewMatrix         Angle ín degrees.
      \param[in] projectionMatrix   Angle ín degrees.
    */
	void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
};

#endif // _GROUND_H_

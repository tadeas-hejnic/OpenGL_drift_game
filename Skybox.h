//----------------------------------------------------------------------------------------
/**
 * \file       Skybox.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Skybox object
*/
//----------------------------------------------------------------------------------------

#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#pragma once
#include "Object.h"
#include "SkyboxShader.h"


class Skybox : public ObjectInstance {
	SkyboxShader * skybox_shader;	///< Shader.
	float currentTime;				///< Current time.

	// Geometry loader.
    /**
      Loads skybox geometry.
    */
	void loadGeometry();
public:
	/// Constructor.
    /**
      Sets the default values and calls the function for loading geometry.

      \param[in] elapsedTime        Elapsed time.
      \param[in] file_name       	Pointer to shader for this skybox object.
    */
	Skybox(float elapsedTime, std::string file_name);

	virtual void update(const float elapsedTime, const glm::mat4* parentModelMatrix) { return; }
	virtual void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
};

#endif // _SKYBOX_H_


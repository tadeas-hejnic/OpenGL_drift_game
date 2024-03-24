//----------------------------------------------------------------------------------------
/**
 * \file       Anim.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Object with animated texture
 *
*/
//----------------------------------------------------------------------------------------

#ifndef _ANIM_H_
#define _ANIM_H_

#pragma once
#include "Object.h"
#include "AnimShader.h"
#include "Elipse.h"


class Anim : public ObjectInstance {
private:
	float startTime;			///< Start time.
	float currentTime;			///< Current time.

	float size;					///< Size of the object.
	glm::vec3 position;			///< Object position.
	glm::vec3 direction;		///< Object direction.

	float frameDuration;		///< Animation frame duration.
	int numOfFrames;			///< Animation number of frames.
	AnimShader * banner_shader;	///< Shader.

	Elipse * elipse;			///< Elipse.

	/// Geometry loader.
    /**
      Loads geometry from prepared C array.

      \param[in] name    Name of the texture.
    */
	void loadGeometry(std::string & name);
public:
	float rotation_angle;		///< Object rotation angle.
	float time_to_live;			///< Object ttl.

	/// Constructor.
    /**
      Sets the default values and calls the function for loading geometry.

      \param[in] elapsedTime    Elapsed time in the game.
      \param[in] pos            Position of this object in the scene.
      \param[in] shdrPrg        Pointer to shader for this object.
    */
	Anim(float elapsedTime, const glm::vec3& pos, AnimShader* shdrPrg);

	/// Constructor.
    /**
      Sets the default values and calls the function for loading geometry.

      \param[in] elapsedTime    Elapsed time in the game.
	  \param[in] shdrPrg        Pointer to shader for this object.
	  \param[in] pos            Position of this object in the scene.
	*/
	Anim(float elapsedTime, AnimShader* shdrPrg, const glm::vec3& pos);
	
	/// Update.
    /**
      Updates the time.

      \param[in] elapsedTime         Elapsed time.
      \param[in] parentModelMatrix   Parent model matrix.
    */
	void update(const float elapsedTime, const glm::mat4* parentModelMatrix) override;

	/// Draw.
    /**
      Sets the uniforms and draw the object.

      \param[in] viewMatrix         View matrix.
      \param[in] projectionMatrix   Projection matrix.
    */
	void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

	/// Time to live is out. 
	/**
	  Return true if time to live has ran out.
	*/
	bool isDead();
};


typedef std::vector<Anim*> BannerList;

#endif // _ANIM_H_

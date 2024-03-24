//----------------------------------------------------------------------------------------
/**
 * \file       Obstacle.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Obstacle object
 *
*/
//----------------------------------------------------------------------------------------

#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#pragma once
#include "Object.h"


typedef struct _Parameters {
	std::string file_name;
	float size;
	glm::vec3 position;
	float rotation;
} Parameters;

typedef struct _LoaderParameters {
	std::string texture_name;
	const float * vertices;
	const unsigned numOfTriangles;
	const unsigned attribsPerVertex;
} LoaderParameters;


static const Parameters DEFAULT_PARAMS = { "", 0.05f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f};

class Obstacle : public ObjectInstance {
public: 
	/// Constructor.
    /**
      Sets the default values and calls the function for loading geometry.

      \param[in] params        Struct of object paramters (file_name, size, position, rotation).
      \param[in] shdrPrg       Pointer to shader for this obstacle object.
    */	
	Obstacle(
		Parameters params,
		CommonShader* shdrPrg = nullptr
	);

	/// Constructor.
    /**
      Sets the default values and calls the function for loading geometry.

      \param[in] params        Struct of object paramters (file_name, size, position, rotation).
      \param[in] shdrPrg       Pointer to shader for this obstacle object.
      \param[in] texture_name  Texture name.
    */
	Obstacle(
		Parameters params,
		CommonShader * shdrPrg,
		std::string texture_name
	);

	/// Constructor.
    /**
      Sets the default values and calls the function for loading geometry from prepared C array.

      \param[in] params        	Struct of object paramters (file_name, size, position, rotation).
      \param[in] shdrPrg       	Pointer to shader for this obstacle object.
      \param[in] hardcore  		If should be load from array.
    */
	Obstacle(
		Parameters params,
		CommonShader* shdrPrg,
		bool hardcore
	);

	/// Geometry loader.
    /**
      Loads geometry from prepared C array.
    */
	virtual void loadGeometry();

	void update(const float elapsedTime, const glm::mat4* parentModelMatrix) override;
	void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
	

	glm::vec3 position;		///< Obstacle position.
	float rotation_angle;	///< Obstacle rotation angle.
	float size;				///< Obstacle size.
};

typedef std::vector<Obstacle*> ObstacleList;

#endif // _OBSTACLE_H_

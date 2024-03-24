#pragma once
#include "Object.h"
#include "AnimShader.h"


class Banner : public ObjectInstance {
	float startTime;
	float currentTime;

	float size;
	glm::vec3 position;
	glm::vec3 direction;
	// float rotation_angle;

	float frameDuration;
	int numOfFrames;
	AnimShader * banner_shader;


	void loadGeometry();
public:
	float rotation_angle;
	Banner(float elapsedTime, const glm::vec3& pos, AnimShader* shdrPrg);

	/**
	* \brief Recalculates the global matrix and updates all children.
	*   Derived classes should also call this method (using ObjectInstance::update()).
	* \param elapsedTime time value in seconds, such as 0.001*glutGet(GLUT_ELAPSED_TIME) (conversion milliseconds => seconds)
	* \param parentModelMatrix parent transformation in the scene-graph subtree
	*/
	void update(const float elapsedTime, const glm::mat4* parentModelMatrix) override;

	/**
	 * \brief Draw instance geometry and calls the draw() on child nodes.
	 */
	void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

};


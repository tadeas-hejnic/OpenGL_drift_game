//----------------------------------------------------------------------------------------
/**
 * \file       Car.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Car object that can be driven
 *
*/
//----------------------------------------------------------------------------------------

#ifndef _CAR_H_
#define _CAR_H_

#pragma once
#include "Object.h"
#include "pgr.h"
#include "parameters.h"


class Car;

typedef std::vector<Car*> CarList;

class Car : ObjectInstance {
	/// Valid angle.
    /**
      Correct the angle to range 0-360 if needed.

      \param[in] angle    Angle in degrees.
      \returns Valid angle in degrees.
    */
	static float get_valid_angle(float angle);

	/// Valid position - in bounds.
    /**
      Checks if the position is in bounds.

      \param[in] pos	Position of the car.
      \returns True if in bounds, otherwise false.
    */
	static bool inBounds(glm::vec3 pos);

	glm::vec3 startPos;			///< Car position after restart.
	float startAngle;			///< Start view angle after restart.
	float timeOfLastCrash;		///< Time of the last crash.
	float startTime;            ///< Time of creation of this car.

public:
	/// Constructor.
    /**
      Sets the default values and calls the function for loading geometry.

      \param[in] elapsedTime    Elapsed time in the game.
      \param[in] shdrPrg        Pointer to shader for this car object.
      \param[in] pos            Position of this car in the scene.
      \param[in] id            	Id for object picking.
    */
	Car(float elapsedTime, CommonShader * shdrPrg, glm::vec3 pos, std::string file_name, int id);

	/// Draw.
    /**
      Sets the uniforms and draw the object.

      \param[in] viewMatrix         View matrix.
      \param[in] projectionMatrix   Projection matrix.
    */
	void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
	void update(const float elapsedTime, const glm::mat4* parentModelMatrix) override;

	/// Reset.
    /**
      Sets the all variables to default values.

      \param[in] elapsedTime    Time.
    */
	void reset(const float elapsedTime);

	/// Speed increase.
    /**
      Increase the speed of the car.

      \param[in] deltaSpeed     Speed delta.
      \param[in] max     		Max car speed.
    */
	void increaseSpeed(float deltaSpeed = CAR_SPEED_INCREMENT, float max = CAR_SPEED_MAX);

	/// Speed decrease.
    /**
      Decrease the speed of the car.

      \param[in] deltaSpeed     Speed delta.
	  \param[in] min     		Minimum car speed.
    */
	void decreaseSpeed(float deltaSpeed = CAR_SPEED_INCREMENT, float min = CAR_SPEED_MIN);

	/// Left turn.
    /**
      Changes the view angle of the object.

      \param[in] deltaAngle     Angle delta.
    */
	void turnLeft(float deltaAngle);

	/// Right turn.
    /**
      Changes the view angle of the object.

      \param[in] deltaAngle     Angle delta.
    */
	void turnRight(float deltaAngle);

	/// Car drift.
    /**
      Sets the drifting variables calls the particular methods if needed.

      \param[in] turn     False when the car goes straight.
    */
	void drift(bool turn);

	/// Car drift stop.
    /**
      Sets the drifting variable to default.
    */
	void driftStop();

	/// Car turn stop.
    /**
      Sets the turning variables to default.
    */
	void straight();

	/// Car drift.
    /**
      Breaks the car.

      \param[in] delta    Car speed delta.
    */
	void breakCar(float delta = BREAK_CAR_DELTA);

	/// Car crash.
    /**
      Decrease the speed.
    */
	void crash();

	/// Gain points.
    /**
      Adds points.
    */
	bool gainPoints();

	/// Gain points.
    /**
      Sets the variable based on parameter.

      \param[in] bool    Is the car driven.
    */
	void isDriven(bool = false);


	int m_id;

	float hp;
	float points;

	glm::vec3 position;         ///< Car position.
	float viewAngle;            ///< Car view angle.
	glm::vec3 direction;        ///< Car direction.
	float speed;                ///< Car speed.
	float size;                 ///< Car size.
	bool destroyed;
	float currentTime;          ///< Current time.


	float prev_view_angle;      ///< View angle in the previous frame.
	bool is_turning;            ///< True if car is turning.
	bool is_drifting;           ///< True if car is drifting.
	bool is_turning_right;		///< True if car is turning right.
	bool is_driven;				///< True if car is driven.
};

#endif // _CAR_H_

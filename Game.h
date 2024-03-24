//----------------------------------------------------------------------------------------
/**
 * \file       Game.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Main game object that is called from functions in main.cpp
 *
 * Runs the main events in the game, holds pointers to all objects in the scene.
 *
*/
//----------------------------------------------------------------------------------------

#ifndef _GAME_H_
#define _GAME_H_


#pragma once
#include <list>
#include "pgr.h"
#include "parameters.h"
#include "Car.h"
#include "CommonShader.h"
#include "Ground.h"
#include "Obstacle.h"
#include "MovingObstacle.h"
#include "Anim.h"
#include "Banner.h"
#include "Skybox.h"


struct GameState {
	int windowWidth;    // set by reshape callback
	int windowHeight;   // set by reshape callback

	bool keyMap[KEYS_COUNT];    // false

	float elapsedTime;

	int cameraMode;

	float cameraElevationAngle; // in degrees = initially 0.0f
	float cameraRotationAngle; // in degrees = initially 0.0f

	bool gameOver;
	bool useFog;
};


struct GameObjects {
	Car * car;
	CarList cars;

	MovingObstacle * shopping_cart;

	ObstacleList big_obstacles;
	
	ObjectList pneu_obstacles;
	ObjectList pots;

	Anim * animal;
	Banner * banner;

	Skybox * skybox;
	Ground * ground;
	
	Anim * coin;
};

class Game {
private:
	size_t current_car_index;		///< Car id of current driven car.
	float lampIntensity;			///< Street lamps light intesnity.
	float sunIntensity;				///< Sun light intesnity.
	bool isDay;						///< Day/night mode variable.

	CommonShader * commonShader;	///< Common shader used by most of the objects.
	AnimShader * coin_shader;		///< Coin shader used for coin animation.

	static bool pointInSphere(const glm::vec3& point, const glm::vec3& center, float radius);
	
	void insertCoin();
public:
	/// Constructor.
    /**
      Sets the default values - window width and height.
      Sets the elapsed time and sets the default values of key map.
    */
	Game();

	/// Destructor.
    /**
      Deletes car and ground object.
    */
	~Game();

	/// Game initialization.
    /**
      Sets the remaining variables.
      Initialize the OpenGL context.
      Calls the Restart method.
    */
	void Init();

    /// Game restart.
    /**
      Sets all variables and objects to default values.
    */
	void Restart();

    /// Game update.
    /**
      Updates all updatable objects in the scene.
    */
	void Update();

    /// Game finalize.
    /**
      Deletes all objects in the scene.
    */
	void Finalize();

    /// Draw window contents.
    /**
      Sets the common uniforms of shaders
      and calls draw methods of every object in the scene.
    */
	void drawWindowContents();

	/// Chenge the car 
    /**
      Sets the driven car to the next in CarList.
    */
	void switchCar();

	/// Chenge the car 
    /**
      Sets the driven car to car with given ID.

      \param[in] carID    ID of the car.
    */
	void switchCar(int carID);

	/// Switch the view.
    /**
      Switch the view.
    */
	void switchView(int mode);

	/// Increase light intensity.
    /**
      Increases street lights intensity.
    */
	void lightIntensityUp();

	/// Decrease light intensity.
    /**
      Decreases street lights intensity.
    */
	void lightIntensityDown();

	/// Change to day state.
    /**
      Sets all variables to day state mode.
    */
	void DayState();

	/// Change to night state.
    /**
      Sets all variables to night state mode.
    */
	void NightState();

	/// Fog switcher.
    /**
      Turns on/off the fog.
    */
	void Fog();

	/// Collision checker.
    /**
      Checks all car collisions with other object in the scene.
    */
	void checkCarColisions();

	GameState m_state;				///< Struct with game state variables.
	GameObjects m_objects;			///< Struct with all game objects.
};

#endif // _GAME_H_

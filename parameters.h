
#ifndef __DATA_H
#define __DATA_H

#define WINDOW_WIDTH   1920
#define WINDOW_HEIGHT  1080
#define WINDOW_TITLE   "Drift Game"

// keys used in the key map
enum { KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_SPACE, KEYS_COUNT
};

enum {
    UP_STATIC_VIEW,
    SIDE_STATIC_VIEW,
    CAR_VIEW
};

// 1.4, 1.92, 00 | 1.5, -1.9 | -1.45, -1.96 | -1.5, 1.9
#define MAP_WIDTH 1.5f
#define MAP_HEIGHT 1.95f

#define SCENE_WIDTH  1.92f
#define SCENE_HEIGHT 1.08f
#define SCENE_DEPTH  1.0f

#define CAMERA_ELEVATION_MAX 45.0f

#define DRIFT 35.0f
#define LEFT_DRIFT 35.0f
#define RIGHT_DRIFT -35.0f
#define STRAIGHT_DRIFT 30.0f

#define DEFAULT_OBSTACLE "data/cube.obj"
#define TREE "data/tree_low_poly.obj"
#define LAMP "data/lamp.obj"
#define FENCE "data/fence.obj"
#define PNEU "data/pneu.obj"
#define POT "data/pot.obj"
#define BUILDING "data/shop_new.obj" 
#define GROUND "data/ground.obj"
#define SHOPPING_CART "data/shopping_cart.obj"
#define BANNER "data/banner.png"
#define SKYBOX "data/skybox"
#define SKYBOX_FORMAT ".png"

#define ANIM_SIZE 0.05f
#define BANNER_SIZE 0.07f
#define CAR_SIZE 0.08f
#define SHOPPING_CART_SIZE 0.03f

#define CAR_SPEED_INCREMENT 0.05f
#define CAR_SPEED_MAX 1.0f
#define CAR_SPEED_MIN -0.3f*CAR_SPEED_MAX
#define CAR_DAMAGE 2.0f
#define CAR_DRIFT_ANGLE 4.0f
#define CAR_DRIFT_SPEED_DECREASE 0.04f
#define CAR_NOT_DRIVEN_DECREASE 0.02f
#define CAR_CRASH_TIME_DELTA 0.1f
#define CAR_CRASH_SPEED_DECREASE 1.2f
#define CAR_POINTS_INCREASE 1.0f
#define CAR_TURN_ANGLE_DELTA 4.0f // in degrees
#define BREAK_CAR_DELTA 0.05f

#define MOVING_OBSTACLE_SPEED 0.1f
#define MOVING_OBSTACLE_RADIUS_X 0.3f
#define MOVING_OBSTACLE_RADIUS_Y 0.1f

#define LAMP_INTENSITY_DELTA 0.05f
#define LAMP_INTENSITY_MAX 2.5f
#define LAMP_INTENSITY_MIN 0.0f

static const glm::vec3 ELIPSE_CENTER = glm::vec3(0.8, 1.0, 0.0);
static const glm::vec2 ELIPSE_SIZE = glm::vec2(0.4, 0.2);

static const glm::vec3 BANNER_POSITION = glm::vec3(-1.12f, -0.525f, 0.06f);
static const glm::vec3 ANIMAL_POSITION = glm::vec3(-1.0f, 0.475f, 0.1f);
static const glm::vec3 BUILDING_POSITION = glm::vec3(-1.05f, -0.02f, 0.09f);

#define TREE_Z 0.05f

static const std::vector<glm::vec3> TREE_POSITIONS = {
    // up
    glm::vec3(-0.25f, 0.15f, TREE_Z),
    glm::vec3(0.0f, 0.15f, TREE_Z),
    glm::vec3(0.4f, 0.15f, TREE_Z),
    glm::vec3(0.65f, 0.15f, TREE_Z),
    glm::vec3(1.05f, 0.15f, TREE_Z),
    glm::vec3(1.3f, 0.15f, TREE_Z),

    // bottom
    glm::vec3(-0.25f, -0.21f, TREE_Z),
    glm::vec3(0.0f, -0.21f, TREE_Z),
    glm::vec3(0.4f, -0.21f, TREE_Z),
    glm::vec3(0.65f, -0.21f, TREE_Z),
    glm::vec3(1.05f, -0.21f, TREE_Z),
    glm::vec3(1.3f, -0.21f, TREE_Z),
};

#define POT_Z -0.05f

static const std::vector<std::pair<glm::vec3, float>> POT_POSITIONS = {
    // up
    {glm::vec3(-0.12f, 0.15f, POT_Z), 0.0f},
    {glm::vec3(0.52f, 0.15f, POT_Z), 0.0f},
    {glm::vec3(1.17f, 0.15f, POT_Z), 0.0f},

    // bottom
    {glm::vec3(-0.12f, -0.21f, POT_Z), 0.0f},
    {glm::vec3(0.52f, -0.21f, POT_Z), 0.0f},
    {glm::vec3(1.17f, -0.21f, POT_Z), 0.0f},

    // ---------------------------------------
    
    // up
    {glm::vec3(1.17f, 0.52f, POT_Z), 0.0f},
    {glm::vec3(0.52f, 0.52f, POT_Z), 0.0f},
    {glm::vec3(-0.12f, 0.52f, POT_Z), 0.0f},
    {glm::vec3(1.17f, 1.7f, POT_Z), 0.0f},
    {glm::vec3(0.52f, 1.7f, POT_Z), 0.0f},
    {glm::vec3(-0.12f, 1.7f, POT_Z), 0.0f},
    {glm::vec3(-0.92f, 1.7f, POT_Z), 0.0f},

    // bottom
    {glm::vec3(1.17f, -0.47f, POT_Z), 0.0f},
    {glm::vec3(0.52f, -0.47f, POT_Z), 0.0f},
    {glm::vec3(-0.12f, -0.47f, POT_Z), 0.0f},
    {glm::vec3(1.17f, -1.7f, POT_Z), 0.0f},
    {glm::vec3(0.52f, -1.7f, POT_Z), 0.0f},
    {glm::vec3(-0.12f, -1.7f, POT_Z), 0.0f},
    {glm::vec3(-0.92f, -1.7f, POT_Z), 0.0f},
    
};

#define LAMP_Z 0.1f

static const std::vector<std::pair<glm::vec3, float>> LAMP_POSITIONS = {
    // up
    {glm::vec3(-0.12f, 0.18f, LAMP_Z), 0.0f},
    {glm::vec3(0.52f, 0.18f, LAMP_Z), 0.0f},
    {glm::vec3(1.17f, 0.18f, LAMP_Z), 0.0f},

    // bottom
    {glm::vec3(-0.12f, -0.24f, LAMP_Z), 180.0f},
    {glm::vec3(0.52f, -0.24f, LAMP_Z), 180.0f},
    {glm::vec3(1.17f, -0.24f, LAMP_Z), 180.0f},

    // ---------------------------------------
    
    // up
    {glm::vec3(1.17f, 0.49f, LAMP_Z), 180.0f},
    {glm::vec3(0.52f, 0.49f, LAMP_Z), 180.0f},
    {glm::vec3(-0.12f, 0.49f, LAMP_Z), 180.0f},
    {glm::vec3(1.17f, 1.73f, LAMP_Z), 0.0f},
    {glm::vec3(0.52f, 1.73f, LAMP_Z), 0.0f},
    {glm::vec3(-0.12f, 1.73f, LAMP_Z), 0.0f},
    {glm::vec3(-0.92f, 1.73f, LAMP_Z), 0.0f},

    // bottom
    {glm::vec3(1.17f, -0.45f, LAMP_Z), 0.0f},
    {glm::vec3(0.52f, -0.45f, LAMP_Z), 0.0f},
    {glm::vec3(-0.12f, -0.45f, LAMP_Z), 0.0f},
    {glm::vec3(1.17f, -1.73f, LAMP_Z), 180.0f},
    {glm::vec3(0.52f, -1.73f, LAMP_Z), 180.0f},
    {glm::vec3(-0.12f, -1.73f, LAMP_Z), 180.0f},
    {glm::vec3(-0.92f, -1.73f, LAMP_Z), 180.0f},

    
};

static const std::vector<std::pair<glm::vec3, size_t>> FENCE_POSITIONS_1 = {
    {glm::vec3(-1.5f, 2.0f, 0.0f), 31},
    {glm::vec3(-1.5f, -2.0f, 0.0f), 31},
};

static const std::vector<std::pair<glm::vec3, size_t>> FENCE_POSITIONS_2 = {
    {glm::vec3(-1.56f, -1.95f, 0.0f), 40},
    {glm::vec3(1.56f, -1.95f, 0.0f), 18},
    {glm::vec3(1.56f, 0.2f, 0.0f), 19},
    // {glm::vec3(1.56f, -0.188f, 0.0f), 1},
};


#define PNEU_Z -0.046f

static const std::vector<std::pair<glm::vec3, size_t>> PNEU_POSITIONS = {
    {glm::vec3(1.56f, 0.0f, PNEU_Z), 3},
    {glm::vec3(1.56f, 0.1f, PNEU_Z), 2},
    {glm::vec3(1.56f, -0.1f, PNEU_Z), 3},
};


static const glm::vec3 CAR_POSITION = glm::vec3(0.0f, 0.3f, 0.0f);

static const std::vector<std::pair<glm::vec3, std::string>> CAR_POSITIONS = {
    {glm::vec3(0.0f, 0.6f, -0.03f), "data/F1_low_poly.obj"},
    {glm::vec3(0.0f, 0.3f, -0.01f), "data/skoda.obj"},
    {glm::vec3(0.0f, -0.3f, -0.02f), "data/camaro.obj"},
    {glm::vec3(0.2f, -0.5f, -0.02f), "data/challenger.obj"},
};

/**
  bench vertex data
*/
const unsigned nBenchAttribsPerVertex = 8; 

const float benchVertices[] = {
    //	   x      y      z		 u		v			nx		ny		nz
        //triangles
        //front face
        -1.0f, -0.35f,  0.35f,	 0.0f, 0.0f,	   0.0f,  0.0f,  -1.0f,	// 1
        1.0f,  -0.35f,  0.35f,	 1.0f, 0.0f,	   0.0f,  1.0f,   0.0f,	// 2
        -1.0f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,   1.0f,	// 3

        1.0f,  -0.35f,  0.35f,	1.0f, 0.0f,		   0.0f,  1.0f,  0.0f,	// 2
        -1.0f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 3
        1.0f,  -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 4

        // left face
        -1.0f, -0.35f,  0.35f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 1
        -1.0f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 3
        -1.0f,  0.35f,  -0.35f,	1.0f, 1.0f, 	  -1.0f, 0.0f,  0.0f,	// 8

        -1.0f, -0.35f,  0.35f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 1
        -1.0f,  0.35f,  0.35f,	 0.0f, 1.0f,  	  -1.0f,  0.0f,  0.0f,	// 6
        -1.0f,  0.35f,  -0.35f,	 1.0f, 1.0f, 	  -1.0f,  0.0f,  0.0f,	// 8

        //right face
        1.0f,  -0.35f,  0.35f,	1.0f, 0.0f,	   0.0f,   0.0f,  1.0f,	// 2
        1.0f,   0.35f,  0.35f,	1.0f, 0.0f,	   0.0f,   0.0f,  1.0f,	// 5
        1.0f,  -0.35f,  -0.35f,	 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,	// 4

        1.0f,  -0.35f,  -0.35f,	 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,	// 4
        1.0f,   0.35f,  0.35f,	1.0f, 0.0f,	   0.0f,   0.0f,  1.0f,	// 5
        1.0f,   0.35f, -0.35f,	1.0f, 0.0f,	   0.0f,   0.0f,  1.0f,	// 7

        // back face	 						   
         1.0f,  0.35f,   0.35f,	 1.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 5
        -1.0f,  0.35f,   0.35f,	 0.0f, 1.0f,  	  -1.0f,  0.0f,  0.0f,	// 6
        -1.0f,  0.35f,  -0.35f,	 1.0f, 1.0f, 	  -1.0f,  0.0f,  0.0f,	// 8

         1.0f,  0.35f,   0.35f,	 1.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 5
         1.0f,  0.35f,  -0.35f,	 1.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 7
        -1.0f,  0.35f,  -0.35f,	 1.0f, 1.0f, 	  -1.0f,  0.0f,  0.0f,	// 8

        // lower face
        -1.0f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 3
         1.0f,  0.35f, -0.35f,	 1.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 7
        -1.0f,  0.35f,  -0.35f,	 1.0f, 1.0f, 	  -1.0f,  0.0f,  0.0f,	// 8


        -1.0f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 3
         1.0f,  0.35f,  -0.35f,	 1.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 7
         1.0f, -0.35f,  -0.35f,	 0.0f, 1.0f,       0.0f,  0.0f,  1.0f,	// 4

        // upper face
        -1.0f, -0.35f,  0.35f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 1
        1.0f,  -0.35f,  0.35f,	1.0f, 0.0f,	       0.0f,  0.0f,  1.0f,	// 2
        1.0f,   0.35f,  0.35f,	 1.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 5 

        -1.0f, -0.35f,  0.35f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 1
        1.0f,   0.35f,  0.35f,	 1.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 5
        -1.0f,  0.35f,  0.35f,	 0.0f, 1.0f,  	  -1.0f,  0.0f,  0.0f,	// 6
        
        // --------------------------------------------

        // left cube
        //triangles
        //front face
        -1.15f, -0.35f,  0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 1
        -1.0f, -0.35f,  0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 2
        -1.15f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 3

        -1.0f, -0.35f,  0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 2
        -1.15f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 3
        -1.0f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 4

        // left face
        -1.15f, -0.35f,  0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 1
        -1.15f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 3
        -1.15f, 0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 8

        -1.15f, -0.35f,   0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 1
        -1.15f,  0.35f,   0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 6
        -1.15f,  0.35f,  -0.35f, 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 8

        //right face
        -1.0f, -0.35f,  0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 2
        -1.0f,  0.35f,  0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 5
        -1.0f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 4

        -1.0f, -0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 4
        -1.0f,  0.35f,  0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 5
        -1.0f,  0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 7

        // done
        // back face	 						   
         -1.0f,  0.35f,  0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 5
        -1.15f,  0.35f,   0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 6
        -1.15f,  0.35f,  -0.35f, 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 8

        -1.0f,  0.35f,  0.65f,	 0.0f, 0.0f,	   0.0f,  0.0f,  1.0f,	// 5
        -1.0f,  0.35f,  -0.35f,	 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 7
        -1.15f,  0.35f,  -0.35f, 0.0f, 1.0f,	   0.0f,  0.0f,  1.0f,	// 8

        // lower face
        -1.15f, -0.35f, -0.35f,  0.0f, 1.0f,       0.0f, 0.0f, 1.0f,	// 3
        -1.0f,   0.35f, -0.35f,  0.0f, 1.0f,       0.0f, 0.0f, 1.0f,	// 7
        -1.15f,  0.35f, -0.35f,  0.0f, 1.0f,       0.0f, 0.0f, 1.0f,	// 8

        -1.15f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 3
        -1.0f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 7
            -1.0f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 4

         // upper face
         -1.15f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 1
            -1.0f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 2
            -1.0f, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 5 

            -1.15f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 1
         -1.0f, 0.35f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 5
         -1.15f, 0.35f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 6
         // --------------------------------------------


         // --------------------------------------------

        // left cube
        //triangles
        //front face
        1.15f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 1
        1.0f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 2
        1.15f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 3

        1.0f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 2
        1.15f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 3
        1.0f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 4

        // left face
        1.15f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 1
        1.15f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 3
        1.15f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 8

        1.15f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 1
        1.15f, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 6
        1.15f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 8
        
        //right face
        1.0f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 2
        1.0f, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 5
        1.0f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 4

        1.0f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 4
        1.0f, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 5
        1.0f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 7

        // done
        // back face	 						   
        1.0f, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 5
        1.15f, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 6
        1.15f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 8

        1.0f, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 5
        1.0f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 7
        1.15f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 8

        // lower face
        1.15f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 3
        1.0f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 7
        1.15f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 8

        1.15f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 3
        1.0f, 0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 7
        1.0f, -0.35f, -0.35f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 4

        // upper face
        1.15f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 1
        1.0f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 2
        1.0f, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 5 

        1.15f, -0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 1
        1.0f, 0.35f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 5
        1.15f, 0.35f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// 6
};
const unsigned benchNumberTriangles = 36;


//
// banner billboard geometry definition 
//
const int animNumQuadVertices = 4;
const float animVertexData[] = {
    // x      y     z     u     v
    -1.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     1.0f,  0.0f, -1.0f,  1.0f, 0.0f,
    -1.0f,  0.0f,  1.0f,  0.0f, 1.0f,
     1.0f,  0.0f,  1.0f,  1.0f, 1.0f,
};

const int bannerNumQuadVertices = 4;
const float bannerVertexData[] = {
    // x      y     z     u     v
    -0.6f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.6f,  0.0f, -1.0f,  1.0f, 0.0f,
    -0.6f,  0.0f,  1.0f,  0.0f, 1.0f,
     0.6f,  0.0f,  1.0f,  1.0f, 1.0f,
};


#endif // __DATA_H

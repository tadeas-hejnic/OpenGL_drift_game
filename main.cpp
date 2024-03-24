#include <time.h>
#include "pgr.h"
#include "Game.h"

#include <iostream>

Game * game = new Game();


// Called to update the display. You should call glutSwapBuffers after all of your
// rendering to display what you rendered.
void displayCallback() {
  GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
  mask |= GL_STENCIL_BUFFER_BIT;

  glClear(mask);

  game->drawWindowContents();

  glutSwapBuffers();
}

// Called whenever the window is resized. The new window size is given, in pixels.
// This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshapeCallback(int newWidth, int newHeight) {

  game->m_state.windowWidth = newWidth;
  game->m_state.windowHeight = newHeight;

  glViewport(0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
}


void updateObjects(float elapsedTime) {
    game->Update();
}


// Callback responsible for the scene update
void timerCallback(int) {

  // update scene time
  game->m_state.elapsedTime = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME); // milliseconds => seconds

    // call appropriate actions according to the currently pressed keys in key map
    // (combinations of keys are supported but not used in this implementation)
    if(game->m_state.keyMap[KEY_RIGHT_ARROW] == true)
        game->m_objects.car->turnRight(CAR_TURN_ANGLE_DELTA);

    if(game->m_state.keyMap[KEY_LEFT_ARROW] == true)
        game->m_objects.car->turnLeft(CAR_TURN_ANGLE_DELTA);

    if(game->m_state.keyMap[KEY_UP_ARROW] == true)
        game->m_objects.car->increaseSpeed();

    if(game->m_state.keyMap[KEY_DOWN_ARROW] == true)
        game->m_objects.car->decreaseSpeed();

    if (game->m_state.keyMap[KEY_SPACE] == true)
        game->m_objects.car->drift(
            (game->m_state.keyMap[KEY_LEFT_ARROW] || game->m_state.keyMap[KEY_RIGHT_ARROW])
                );

  
  // update objects in the scene
  updateObjects(game->m_state.elapsedTime);
    // game->Update();
  // set timeCallback next invocation
  glutTimerFunc(33, timerCallback, 0);

  glutPostRedisplay();
}


// Called when mouse is moving while no mouse buttons are pressed.
void passiveMouseMotionCallback(int mouseX, int mouseY) {

    if (mouseY != game->m_state.windowHeight / 2) {

        float cameraElevationAngleDelta = -0.5f * (mouseY - game->m_state.windowHeight / 2);

        if (fabs(game->m_state.cameraElevationAngle + cameraElevationAngleDelta) < CAMERA_ELEVATION_MAX)
            game->m_state.cameraElevationAngle += cameraElevationAngleDelta;

        // set mouse pointer to the window center
        glutWarpPointer(game->m_state.windowWidth / 2, game->m_state.windowHeight / 2);

        glutPostRedisplay();
    }

    if (mouseX != game->m_state.windowWidth / 2) {

        float cameraRotationAngleDelta = -0.5f * (mouseX - game->m_state.windowWidth / 2);

        if (fabs(game->m_state.cameraRotationAngle + cameraRotationAngleDelta) < CAMERA_ELEVATION_MAX)
            game->m_state.cameraRotationAngle += cameraRotationAngleDelta;

        // set mouse pointer to the window center
        glutWarpPointer(game->m_state.windowWidth / 2, game->m_state.windowHeight / 2);

        glutPostRedisplay();
    }
}


// Called whenever a key on the keyboard was pressed. The key is given by the "keyPressed"
// parameter, which is in ASCII. It's often a good idea to have the escape key (ASCII value 27)
// to call glutLeaveMainLoop() to exit the program.
void keyboardCallback(unsigned char keyPressed, int mouseX, int mouseY) {
  
  switch(keyPressed) {
    case 27: // escape
#ifndef __APPLE__
        glutLeaveMainLoop();
#else
        exit(0);
#endif
      break;
    case 'd':
        game->m_state.keyMap[KEY_RIGHT_ARROW] = true;
        break;
    case 'a':
        game->m_state.keyMap[KEY_LEFT_ARROW] = true;
        break;
    case 'w':
        game->m_state.keyMap[KEY_UP_ARROW] = true;
        break;
    case 's':
        game->m_state.keyMap[KEY_DOWN_ARROW] = true;
        break;
    case ' ': // drift
      if(game->m_state.gameOver != true)
          game->m_state.keyMap[KEY_SPACE] = true;
      break;
    case 'b': // break
        if (game->m_state.gameOver != true)
            game->m_objects.car->breakCar();
        break;
    case 'x': // switch cars
        if (game->m_state.gameOver != true)
            game->switchCar();
        std::cout << "switchCar" << std::endl;
        break;
    case 'f': // break
        game->Fog();
        break;
    default:
      ; // printf("Unrecognized key pressed\n");
  }
}

// Called whenever a key on the keyboard was released. The key is given by
// the "keyReleased" parameter, which is in ASCII. 
void keyboardUpCallback(unsigned char keyReleased, int mouseX, int mouseY) {

  switch(keyReleased) {
    case ' ':
        game->m_state.keyMap[KEY_SPACE] = false;
        game->m_objects.car->driftStop();
      break;
    case 'd':
        game->m_state.keyMap[KEY_RIGHT_ARROW] = false;
        game->m_objects.car->straight();
        break;
    case 'a':
        game->m_state.keyMap[KEY_LEFT_ARROW] = false;
        game->m_objects.car->straight();
        break;
    case 'w':
        game->m_state.keyMap[KEY_UP_ARROW] = false;
        break;
    case 's':
        game->m_state.keyMap[KEY_DOWN_ARROW] = false;
        break;
    default:
      ; // printf("Unrecognized key released\n");
  }
}

// The special keyboard callback is triggered when keyboard function or directional
// keys are pressed.
void specialKeyboardCallback(int specKeyPressed, int mouseX, int mouseY) {

    if(game->m_state.gameOver == true)
        return;

    switch (specKeyPressed) {
        case GLUT_KEY_RIGHT:
            game->m_state.keyMap[KEY_RIGHT_ARROW] = true;
            break;
        case GLUT_KEY_LEFT:
            game->m_state.keyMap[KEY_LEFT_ARROW] = true;
            break;
        case GLUT_KEY_UP:
            game->m_state.keyMap[KEY_UP_ARROW] = true;
            break;
        case GLUT_KEY_DOWN:
            game->m_state.keyMap[KEY_DOWN_ARROW] = true;
            break;
        case GLUT_KEY_F1:
            game->switchView(UP_STATIC_VIEW);
            glutPassiveMotionFunc(NULL);
            break;
        case GLUT_KEY_F2:
            game->switchView(SIDE_STATIC_VIEW);
            glutPassiveMotionFunc(passiveMouseMotionCallback);
            glutWarpPointer(game->m_state.windowWidth / 2, game->m_state.windowHeight / 2);
            break;
        case GLUT_KEY_F3:
            game->switchView(CAR_VIEW);
            glutPassiveMotionFunc(NULL);
            break;
        default:;
  }
}

// The special keyboard callback is triggered when keyboard function or directional
// keys are released.
void specialKeyboardUpCallback(int specKeyReleased, int mouseX, int mouseY) {

  if(game->m_state.gameOver == true)
    return;

  switch (specKeyReleased) {
	case GLUT_KEY_RIGHT:
      game->m_state.keyMap[KEY_RIGHT_ARROW] = false;
      game->m_objects.car->straight();
      break;
    case GLUT_KEY_LEFT:
      game->m_state.keyMap[KEY_LEFT_ARROW] = false;
      game->m_objects.car->straight();
      break;
    case GLUT_KEY_UP:
      game->m_state.keyMap[KEY_UP_ARROW] = false;
      break;
    case GLUT_KEY_DOWN:
      game->m_state.keyMap[KEY_DOWN_ARROW] = false;
      break;
		default:
      ; // printf("Unrecognized special key released\n");
  }
}

void mouseCallback(int buttonPressed, int buttonState, int mouseX, int mouseY) {
    switch (buttonPressed) {
        case 3:  //mouse wheel scrolls
            game->lightIntensityUp();
            break;
        case 4:
            game->lightIntensityDown(); 
            break;
        default:
            break;
    }

    // do picking only on mouse down
    if ((buttonPressed == GLUT_LEFT_BUTTON) && (buttonState == GLUT_DOWN)) {

        // store value from the stencil buffer (byte)
        unsigned char carID = 0;
       
        glReadPixels(mouseX, game->m_state.windowHeight - 1 - mouseY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &carID);


        // the buffer was initially cleared to zeros
        if (carID == 0) {
            // background was clicked
            printf("Clicked on background\n");
        }
        else {
            // object was clicked
            printf("Clicked on object with ID: %d\n", (int)carID);

            game->switchCar((int)carID);
        }
    }
}


void finalizeApplication(void) {
    game->Finalize();
}


int main(int argc, char** argv) {

  // initialize windowing system
  glutInit(&argc, argv);

#ifndef __APPLE__
  glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
#else
  glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
#endif

  // initial window size
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow(WINDOW_TITLE);

  glutDisplayFunc(displayCallback);
  // register callback for change of window size
  glutReshapeFunc(reshapeCallback);
  // register callbacks for keyboard
  glutKeyboardFunc(keyboardCallback);
  glutKeyboardUpFunc(keyboardUpCallback);
  glutSpecialFunc(specialKeyboardCallback);     // key pressed
  glutSpecialUpFunc(specialKeyboardUpCallback); // key released


  glutMouseFunc(mouseCallback);

  glutTimerFunc(33, timerCallback, 0);

  // initialize PGR framework (GL, DevIl, etc.)
  if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
      pgr::dieWithError("pgr init failed, required OpenGL not supported?");

  // initializeApplication();
  game->Init();

#ifndef __APPLE__
  glutCloseFunc(finalizeApplication);
#else
  glutWMCloseFunc(finalizeApplication);
#endif

  glutMainLoop();

  return 0;
}

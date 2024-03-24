#include "Game.h"
#include "Obstacle.h"
#include "MovingObstacle.h"
#include "Skybox.h"
#include <iostream>


bool Game::pointInSphere(const glm::vec3& point, const glm::vec3& center, float radius) {
    float dist = distance(glm::vec3(point.x, point.y, 0.0f), glm::vec3(center.x, center.y, 0.0f));
    if (dist < radius) return true;

    return false;
}

void Game::insertCoin() {
    if (!m_objects.coin) {
        m_objects.coin = new Anim(
            m_state.elapsedTime,
            coin_shader,
            m_objects.car->position + glm::vec3(0.0, 0.0, 0.03)
        );
    }
}

Game::Game() {
	m_state.elapsedTime = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME);
	m_state.windowHeight = WINDOW_HEIGHT;
	m_state.windowWidth = WINDOW_WIDTH;

	for (auto key : m_state.keyMap)
		key = false;

    current_car_index = 0;
}

Game::~Game() {
	delete m_objects.car;
	m_objects.car = nullptr;

    delete m_objects.ground;
    m_objects.ground = nullptr;
}

void Game::Init() {
	srand((unsigned int)time(NULL));

	// initialize OpenGL
	glClearColor(0.3f, 0.1f, 0.1f, 1.0f);
	glClearStencil(0); 
	glEnable(GL_DEPTH_TEST);

    m_state.cameraMode = CAR_VIEW;

    m_objects.shopping_cart = nullptr;
	m_objects.car = nullptr;
    m_objects.ground = nullptr;

    m_objects.animal = nullptr;
    m_objects.banner = nullptr;
    m_objects.coin = nullptr;

    coin_shader = new AnimShader();
    coin_shader->moving = false;
    coin_shader->ShaderInit();

    commonShader = new CommonShader();
    commonShader->ShaderInit();

	Restart();
}

void Game::Restart() {
	m_state.elapsedTime = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME); // milliseconds => seconds
    
    m_objects.cars.clear();
    for (int i = 0; i < CAR_POSITIONS.size(); i++)
        m_objects.cars.push_back(new Car(
            m_state.elapsedTime, 
            commonShader, 
            CAR_POSITIONS[i].first,
            CAR_POSITIONS[i].second, i+1));
    
    for (auto car : m_objects.cars)
        car->reset(m_state.elapsedTime);

    if (!m_objects.car) {
        m_objects.car = m_objects.cars[0];
        m_objects.car->isDriven(true);
    }
   
    if (!m_objects.ground)
        m_objects.ground = new Ground(commonShader);


    if (!m_objects.animal) {
        m_objects.animal = new Anim(
            m_state.elapsedTime,
            ANIMAL_POSITION,
            nullptr
        );
    }


    if (!m_objects.banner) {
        m_objects.banner = new Banner(
            m_state.elapsedTime,
            BANNER_POSITION,
            nullptr
        );
    }

    // POTS
    m_objects.pots.clear();
    for (int i = 0; i < POT_POSITIONS.size(); i++)
        m_objects.pots.push_back(new Obstacle(
            { POT, 0.2f, POT_POSITIONS[i].first, POT_POSITIONS[i].second },
            commonShader
        ));

    m_objects.shopping_cart = new MovingObstacle(m_state.elapsedTime, commonShader, glm::vec3(1.0f, 0.0f, 0.1f), SHOPPING_CART);

    m_objects.big_obstacles.clear();
    m_objects.big_obstacles.push_back(new Obstacle(
        { BUILDING, 0.5f, BUILDING_POSITION, -90.0f },
        commonShader
    ));

    // TREES
    for (size_t i = 0; i < TREE_POSITIONS.size(); i++)
        m_objects.big_obstacles.push_back(new Obstacle(
            { TREE, 0.1f, TREE_POSITIONS[i], 0.0f },
            commonShader
        ));

    // LAMPS
    for (size_t i = 0; i < LAMP_POSITIONS.size(); i++)
        m_objects.big_obstacles.push_back(new Obstacle(
            { LAMP, 0.15f, LAMP_POSITIONS[i].first, LAMP_POSITIONS[i].second },
            commonShader
        ));

    // FENCE
    for (size_t i = 0; i < FENCE_POSITIONS_1.size(); i++)
        for (size_t j = 0; j < FENCE_POSITIONS_1[i].second; j++)
            m_objects.big_obstacles.push_back(new Obstacle(
                { FENCE, 0.05f, FENCE_POSITIONS_1[i].first + glm::vec3(0.1f * j, 0.0f, 0.0f), 90.0f },
                commonShader
            ));

    for (size_t i = 0; i < FENCE_POSITIONS_2.size(); i++)
        for (size_t j = 0; j < FENCE_POSITIONS_2[i].second; j++)
            m_objects.big_obstacles.push_back(new Obstacle(
                { FENCE, 0.05f, FENCE_POSITIONS_2[i].first + glm::vec3(0.0f, 0.1f * j, 0.0f), 0.0f },
                commonShader
            ));

    // BENCH
    m_objects.big_obstacles.push_back(new Obstacle(
        { "", 0.05f, glm::vec3(-1.0f, 0.5f, -0.02f), 0.0f },
        commonShader, true
    ));


    // PNEU OBSTACLES
    m_objects.pneu_obstacles.clear();
    for (size_t i = 0; i < PNEU_POSITIONS.size(); i++)
        for (size_t j = 0; j < PNEU_POSITIONS[i].second; j++)
            m_objects.pneu_obstacles.push_back(new Obstacle(
                { PNEU, 0.02f, PNEU_POSITIONS[i].first + glm::vec3(0.0f, 0.0f, 0.012f * j), 0.0f },
                commonShader
            ));

    m_objects.skybox = new Skybox(m_state.elapsedTime, SKYBOX);


    m_state.cameraMode = CAR_VIEW;

	m_state.cameraElevationAngle = 0.0f;

	// reset key map
	for (size_t i = 0; i < KEYS_COUNT; i++)
		m_state.keyMap[i] = false;

	m_state.gameOver = false;
    lampIntensity = 1.0f;
    sunIntensity = 1.0f;
    isDay = false;
    m_state.useFog = false;
}

void Game::Update() {
    checkCarColisions();

    for (auto car : m_objects.cars)
        car->update(m_state.elapsedTime, nullptr);

    m_objects.shopping_cart->update(m_state.elapsedTime, nullptr);

    if ((int)(m_state.elapsedTime) % 100 < 50 && !isDay)
        DayState();
    else if ((int)(m_state.elapsedTime) % 100 > 50 && isDay)
        NightState();

    m_objects.animal->update(m_state.elapsedTime, nullptr);
    m_objects.banner->update(m_state.elapsedTime, nullptr);

    if (m_objects.coin) {
        m_objects.coin->update(m_state.elapsedTime, nullptr);
        if (m_objects.coin->isDead()) {
            delete m_objects.coin;
            m_objects.coin = nullptr;
        }
    }
}


void Game::drawWindowContents() {

    // setup parallel projection
    glm::mat4 orthoProjectionMatrix = glm::ortho(
        -SCENE_WIDTH, SCENE_WIDTH,
        -SCENE_HEIGHT, SCENE_HEIGHT,
        -10.0f * SCENE_DEPTH, 10.0f * SCENE_DEPTH
    );

    // static viewpoint - top view
    glm::mat4 orthoViewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    // setup camera & projection transform
    glm::mat4 viewMatrix = orthoViewMatrix;
    glm::mat4 projectionMatrix = orthoProjectionMatrix;

    if (m_state.cameraMode == CAR_VIEW) {

        // set camera position behind car

        glm::vec3 cameraPosition, cameraUpVector, cameraViewDirection = glm::vec3(0.0f, 0.0f, 0.0f);

        if (m_objects.car->speed < -0.1f) {
            cameraPosition = m_objects.car->position + 0.3f * m_objects.car->direction + glm::vec3(0.0f, 0.0f, 0.1f);
            cameraUpVector = glm::vec3(0.0f, 0.0f, 1.0f);

            cameraViewDirection = -1.0f * m_objects.car->direction;
        } else {
            cameraPosition = m_objects.car->position - 0.3f * m_objects.car->direction + glm::vec3(0.0f, 0.0f, 0.1f);
            cameraUpVector = glm::vec3(0.0f, 0.0f, 1.0f);

            cameraViewDirection = m_objects.car->direction;

        }
        
        glm::vec3 rotationAxis = glm::cross(cameraViewDirection, cameraUpVector);
        glm::mat4 cameraTransform = glm::rotate(glm::mat4(1.0f), glm::radians(m_state.cameraElevationAngle), rotationAxis);

        cameraUpVector = glm::vec3(cameraTransform * glm::vec4(cameraUpVector, 0.0f));
        cameraViewDirection = glm::vec3(cameraTransform * glm::vec4(cameraViewDirection, 0.0f));


        glm::vec3 cameraCenter = cameraPosition + cameraViewDirection;

        viewMatrix = glm::lookAt(
            cameraPosition,
            cameraCenter,
            cameraUpVector
        );

        projectionMatrix = glm::perspective(glm::radians(60.0f), m_state.windowWidth / (float)m_state.windowHeight, 0.1f, 10.0f);
    
    } else if (m_state.cameraMode == SIDE_STATIC_VIEW) {

        glm::vec3 cameraPosition, cameraUpVector, cameraViewDirection = glm::vec3(0.0f, 0.0f, 0.0f);

        cameraPosition = glm::vec3(-1.0f, 0.0f, 0.25f);
        cameraUpVector = glm::vec3(0.0f, 0.0f, 0.8f);

        cameraViewDirection = glm::vec3(1.0f, 0.0f, 0.0f);
       
        glm::vec3 rotationAxis = glm::cross(cameraViewDirection, cameraUpVector);
        glm::mat4 cameraTransform = glm::rotate(glm::mat4(1.0f), glm::radians(m_state.cameraElevationAngle), rotationAxis);

        cameraUpVector = glm::vec3(cameraTransform * glm::vec4(cameraUpVector, 0.0f));
        
        cameraTransform = glm::rotate(cameraTransform, glm::radians(m_state.cameraRotationAngle), cameraUpVector);
        cameraViewDirection = glm::vec3(cameraTransform * glm::vec4(cameraViewDirection, 0.0f));

        glm::vec3 cameraCenter = cameraPosition + cameraViewDirection;

        viewMatrix = glm::lookAt(
            cameraPosition,
            cameraCenter,
            cameraUpVector
        );

        projectionMatrix = glm::perspective(glm::radians(60.0f), m_state.windowWidth / (float)m_state.windowHeight, 0.1f, 10.0f);
    }

    glUseProgram(commonShader->program);
    glUniform1f(commonShader->locations.time, m_state.elapsedTime);
   
    glUniform3fv(commonShader->locations.reflectorPosition, 1, glm::value_ptr(m_objects.car->position));
    glUniform3fv(commonShader->locations.reflectorDirection, 1, glm::value_ptr(m_objects.car->direction));
    
    glUniform3fv(commonShader->locations.lampPositionLine1, 1, glm::value_ptr(LAMP_POSITIONS[0].first));
    glUniform1i(commonShader->locations.numOfLine1, 3);
    glUniform1f(commonShader->locations.distanceLine1, 0.65f);
    glUniform1f(commonShader->locations.lampIntensity, lampIntensity);
    glUniform1f(commonShader->locations.sunIntensity, sunIntensity);

    glUniform1i(commonShader->locations.useFog, m_state.useFog);
    glUniform3fv(commonShader->locations.carPosition, 1, glm::value_ptr(m_objects.car->position));


    glUseProgram(0);


    for (auto pot : m_objects.pots)
        pot->draw(viewMatrix, projectionMatrix);

    for (auto obstacle : m_objects.big_obstacles)
        obstacle->draw(viewMatrix, projectionMatrix);

    for (auto pneu : m_objects.pneu_obstacles)
        pneu->draw(viewMatrix, projectionMatrix);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    for (auto car : m_objects.cars)
        car->draw(viewMatrix, projectionMatrix);

    // disable stencil test
    glDisable(GL_STENCIL_TEST);
    
    m_objects.ground->draw(viewMatrix, projectionMatrix);
    m_objects.shopping_cart->draw(viewMatrix, projectionMatrix);
    m_objects.skybox->draw(viewMatrix, projectionMatrix);
    m_objects.banner->draw(viewMatrix, projectionMatrix);
    m_objects.animal->draw(viewMatrix, projectionMatrix);
    if(m_objects.coin)
        m_objects.coin->draw(viewMatrix, projectionMatrix);
}


void Game::switchCar() {
    m_objects.car->isDriven();
    current_car_index = (current_car_index + 1) % m_objects.cars.size();
    std::cout << current_car_index << std::endl;
    m_objects.car = m_objects.cars[current_car_index];
    m_objects.car->isDriven(true);
}


void Game::switchCar(int carID) {
    m_objects.car->isDriven();
    m_objects.car = m_objects.cars[carID - 1];
    m_objects.car->isDriven(true);
}


void Game::switchView(int mode) {
    m_state.cameraMode = mode;
    m_state.cameraElevationAngle = 0.0f;
    m_state.cameraRotationAngle = 0.0f;
}


void Game::lightIntensityUp() {
    if (lampIntensity < LAMP_INTENSITY_MAX)
        lampIntensity += LAMP_INTENSITY_DELTA;
}


void Game::lightIntensityDown() {
    if (lampIntensity > LAMP_INTENSITY_MIN)
        lampIntensity -= LAMP_INTENSITY_DELTA;
}


void Game::DayState() {
    isDay = true;
    lampIntensity = 0.0f;
    sunIntensity = 1.0f;
}


void Game::NightState() {
    isDay = false;
    lampIntensity = 1.0f;
    sunIntensity = 0.1f;
}


void Game::Fog() {
    m_state.useFog = !(m_state.useFog);
}


void Game::checkCarColisions() {
    for (auto obstacle : m_objects.big_obstacles)
        if (pointInSphere(m_objects.car->position, obstacle->position, 1.5f * CAR_SIZE))
            m_objects.car->crash();
        else if (pointInSphere(m_objects.car->position, obstacle->position, 2.5f * CAR_SIZE)) {
            if (m_objects.car->gainPoints())
                insertCoin();
        }

    for (auto car : m_objects.cars)
        if (car != m_objects.car) {
            if (pointInSphere(m_objects.car->position, car->position, 1.5f * CAR_SIZE))
                m_objects.car->crash();
            else if (pointInSphere(m_objects.car->position, car->position, 2.5f * CAR_SIZE)) {
                if (m_objects.car->gainPoints())
                    insertCoin();
            }
        }
}


void Game::Finalize() {
    for (auto pot : m_objects.pots) delete pot;
    for (auto obstacle : m_objects.big_obstacles) delete obstacle;
    for (auto pneu_obstacle : m_objects.pneu_obstacles) delete pneu_obstacle;
    for (auto car : m_objects.cars) delete car;
    m_objects.car = nullptr;

    delete m_objects.ground;
    m_objects.ground = nullptr;
    delete m_objects.shopping_cart;
    m_objects.shopping_cart = nullptr;
}

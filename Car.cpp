#include "Car.h"
#include <iostream>


float Car::get_valid_angle(float angle) {
    while (angle < 0) angle += 360.0f;
    while (angle >= 360) angle -= 360.0f;
    return angle;
}

bool Car::inBounds(glm::vec3 pos) {
    if (pos.x > MAP_WIDTH || pos.x < -MAP_WIDTH)
        return false;
    if (pos.y > MAP_HEIGHT || pos.y < -MAP_HEIGHT)
        return false;

    return true;
}

Car::Car(float elapsedTime, CommonShader * shdrPrg, glm::vec3 pos, std::string file_name, int id) {
    if (shdrPrg == nullptr) {
        m_shaderProgram = new CommonShader();
        m_shaderProgram->ShaderInit();
    } else
        m_shaderProgram = shdrPrg;

    startPos = pos;
    startAngle = 0.0f;
    size = CAR_SIZE;

    m_fileName = file_name;
    m_id = id;

    if (loadMultipleMesh() != true) {
        std::cerr << "initializeModels(): Car model loading failed." << std::endl;
    }
    CHECK_GL_ERROR();

    reset(elapsedTime);
}

void Car::reset(const float elapsedTime) {
    hp = 100.0f;
    points = 0.0f;

    position = startPos;
    viewAngle = startAngle;
    direction = glm::vec3(cos(glm::radians(viewAngle)), sin(glm::radians(viewAngle)), 0.0f);
    speed = 0.0f;
    startTime = elapsedTime;
    currentTime = startTime;
    timeOfLastCrash = currentTime;

    prev_view_angle = viewAngle; // degrees

    is_drifting = false;
    is_turning = false;
    is_turning_right = false;
    is_driven = false;

    destroyed = false;
}

void Car::increaseSpeed(float deltaSpeed, float max) {
    if (speed > 0) deltaSpeed *= 2;
    speed = std::min(speed + deltaSpeed, max);
}

void Car::decreaseSpeed(float deltaSpeed, float min) {
    if (is_drifting) speed = std::max(speed - deltaSpeed, 0.0f);
    else speed = std::max(speed - deltaSpeed, min);
}

void Car::turnLeft(float deltaAngle) {
    if (speed == 0) return;

    prev_view_angle = viewAngle;
    viewAngle = get_valid_angle(viewAngle + deltaAngle);

    float angle = glm::radians(viewAngle);

    direction.x = cos(angle);
    direction.y = sin(angle);

    is_turning_right = false;
    is_turning = true;
}

void Car::turnRight(float deltaAngle) {
    if (speed == 0) return;

    prev_view_angle = viewAngle;
    viewAngle = get_valid_angle(viewAngle - deltaAngle);

    float angle = glm::radians(viewAngle);

    direction.x = cos(angle);
    direction.y = sin(angle);

    is_turning_right = true;
    is_turning = true;
}

void Car::drift(bool turn) {
    if (turn && speed > 0) {
        if (is_turning_right)
            turnRight(CAR_DRIFT_ANGLE);
        else
            turnLeft(CAR_DRIFT_ANGLE);
        is_drifting = true;
    } else if (speed > 0) {
        is_drifting = true;
        decreaseSpeed(CAR_DRIFT_SPEED_DECREASE);
    }
    // fast break and move from one side to the other
}

void Car::driftStop() {
    is_drifting = false;
}

void Car::straight() {
    is_turning = false;
}

void Car::breakCar(float delta) {
    if (speed > -0.03f && speed < 0.03f) speed = 0.0f;
    if (speed > 0) decreaseSpeed(delta, 0.0f);
    if (speed < 0) increaseSpeed(delta, 0.0f);
}

void Car::crash() {
    speed /= CAR_CRASH_SPEED_DECREASE;
    if (currentTime - timeOfLastCrash < CAR_CRASH_TIME_DELTA) return;

    timeOfLastCrash = currentTime;
    hp -= CAR_DAMAGE;
}

bool Car::gainPoints() {
    if (is_drifting)
        points += CAR_POINTS_INCREASE;
    return is_drifting && is_turning;
}

void Car::isDriven(bool is_dri) {
    is_driven = is_dri;
}


void Car::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glStencilFunc(GL_ALWAYS, m_id, 255);

    glUseProgram(m_shaderProgram->program);

    // prepare modeling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    if (is_drifting && is_turning) {
        int sgn = 1;
        if ((prev_view_angle - viewAngle) > 0) sgn = -1;
        // std::cout << sgn << std::endl;
        float tmp_angle = get_valid_angle(viewAngle + sgn * DRIFT);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(tmp_angle), glm::vec3(0, 0, 1));
    } else if (is_drifting) {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(viewAngle + sin(10 * currentTime) * STRAIGHT_DRIFT  * speed), glm::vec3(0, 0, 1));
    } else
        modelMatrix = glm::rotate(modelMatrix, glm::radians(viewAngle), glm::vec3(0, 0, 1));

    modelMatrix = glm::scale(modelMatrix, glm::vec3(size, size, size));

    // send matrices to the vertex & fragment shader
    m_shaderProgram->setTransformUniforms(
        modelMatrix, 
        viewMatrix, 
        projectionMatrix
    );

    // Draw each corresponding part of the geometry
    for (size_t i = 0; i < m_multiple_geometry.size(); i++) {
        m_shaderProgram->setMaterialUniforms(
            m_multiple_geometry[i]->ambient,
            m_multiple_geometry[i]->diffuse,
            m_multiple_geometry[i]->specular,
            m_multiple_geometry[i]->shininess,
            m_multiple_geometry[i]->texture
        );
        glBindVertexArray(m_multiple_geometry[i]->vertexArrayObject);
        glDrawElements(GL_TRIANGLES, m_multiple_geometry[i]->numTriangles * 3, GL_UNSIGNED_INT, 0);
    }

    if (m_geometry) {
        m_shaderProgram->setMaterialUniforms(
            m_geometry->ambient,
            m_geometry->diffuse,
            m_geometry->specular,
            m_geometry->shininess,
            m_geometry->texture
        );
        // draw geometry
        glBindVertexArray(m_geometry->vertexArrayObject);
        glDrawElements(GL_TRIANGLES, m_geometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    glUseProgram(0);
}

void Car::update(const float elapsedTime, const glm::mat4* parentModelMatrix) {
    // if (!is_driven && speed > 0.0f) decreaseSpeed(0.03f, 0.0f);
    // else if (!is_driven && speed < 0.0f) increaseSpeed(0.03f, 0.0f);
    if (!is_driven && speed != 0.0f) breakCar(0.01f);

    if (speed == 0.0f) is_drifting = false;

    float timeDelta = elapsedTime - currentTime;
    currentTime = elapsedTime;
    
    glm::vec3 possiblePosition = position + timeDelta * speed * direction;
    
    if (inBounds(possiblePosition))
        position = possiblePosition;

    if (hp <= 0.0f) std::cout << "GAME OVER" << std::endl;
    if (points > 10.0f) std::cout << "WINNER" << std::endl;
    // else std::cout << hp << std::endl;
}

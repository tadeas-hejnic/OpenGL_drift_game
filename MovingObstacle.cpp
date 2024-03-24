#include "MovingObstacle.h"
#include "parameters.h"
#include <iostream>


MovingObstacle::MovingObstacle(float elapsedTime, CommonShader* shdrPrg, glm::vec3 pos, std::string file_name) {
    if (shdrPrg == nullptr) {
        m_shaderProgram = new CommonShader();
        m_shaderProgram->ShaderInit();
    }
    else
        m_shaderProgram = shdrPrg;

    elipse = new Elipse(ELIPSE_CENTER, ELIPSE_SIZE);
    startPos = pos;
    position = startPos;
    startAngle = 0.0f;
    viewAngle = startAngle; // degrees
    direction = glm::vec3(cos(glm::radians(viewAngle)), sin(glm::radians(viewAngle)), 0.0f);

    size = SHOPPING_CART_SIZE;
    currentTime = elapsedTime;
    m_fileName = file_name;

    if (loadMultipleMesh() != true) {
        std::cerr << "initializeModels(): Car model loading failed." << std::endl;
    }
    CHECK_GL_ERROR();
}

void MovingObstacle::update(const float elapsedTime, const glm::mat4* parentModelMatrix) {
	currentTime = elapsedTime;

    position = elipse->getPosition(currentTime);

    viewAngle = elipse->getAngle(currentTime);
}

void MovingObstacle::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(m_shaderProgram->program);

    // prepare modeling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
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

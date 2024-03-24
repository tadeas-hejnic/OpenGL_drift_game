#include "Ground.h"
#include "parameters.h"
#include <iostream>

Ground::Ground(CommonShader* shdrPrg) {
    position = glm::vec3(0.0f, 0.0f, -0.05f);
    size = 2.0f;

    if (shdrPrg == nullptr) {
        m_shaderProgram = new CommonShader();
        m_shaderProgram->ShaderInit();

    } else
        m_shaderProgram = shdrPrg;

    m_fileName = GROUND;
    
    if (loadMultipleMesh() != true) {
        std::cerr << "initializeModels(): Ground model loading failed." << std::endl;
    }
}

void Ground::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(m_shaderProgram->program);

    // prepare modeling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
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

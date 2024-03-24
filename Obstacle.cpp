#include "Obstacle.h"
#include "parameters.h"
#include <iostream>



void Obstacle::loadGeometry() {

    m_geometry = new ObjectGeometry;

    m_geometry->texture = pgr::createTexture("data/wood.jpg");

    glGenVertexArrays(1, &(m_geometry->vertexArrayObject));\
        glBindVertexArray(m_geometry->vertexArrayObject);

    glGenBuffers(1, &(m_geometry->vertexBufferObject));
    glBindBuffer(GL_ARRAY_BUFFER, m_geometry->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(benchVertices), benchVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(m_shaderProgram->locations.position);
    glVertexAttribPointer(m_shaderProgram->locations.position, 3, GL_FLOAT, GL_FALSE, nBenchAttribsPerVertex * sizeof(float), 0);

    glEnableVertexAttribArray(m_shaderProgram->locations.texCoord);
    glVertexAttribPointer(m_shaderProgram->locations.texCoord, 2, GL_FLOAT, GL_FALSE, nBenchAttribsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(m_shaderProgram->locations.normal);
    glVertexAttribPointer(m_shaderProgram->locations.normal, 3, GL_FLOAT, GL_FALSE, nBenchAttribsPerVertex * sizeof(float), (void*)(5 * sizeof(float)));


    m_geometry->ambient = glm::vec3(0.01f);
    m_geometry->diffuse = glm::vec3(0.3f);
    m_geometry->specular = glm::vec3(0.3f);
    m_geometry->shininess = 0.01f;

    glBindVertexArray(0);
    CHECK_GL_ERROR();
    m_geometry->numTriangles = benchNumberTriangles;
}



Obstacle::Obstacle(Parameters params, CommonShader* shdrPrg) {
    if (shdrPrg == nullptr) {
        m_shaderProgram = new CommonShader();
        m_shaderProgram->ShaderInit();
    } else
        m_shaderProgram = shdrPrg;

    position = params.position;
    size = params.size;
    rotation_angle = params.rotation;

    if (params.file_name == "") params.file_name = DEFAULT_OBSTACLE;
    m_fileName = params.file_name;

    if (loadMultipleMesh() != true) {
        std::cerr << "initializeModels(): Obstacle model loading failed." << std::endl;
    }
}


Obstacle::Obstacle(Parameters params, CommonShader* shdrPrg, std::string texture_name) {
    if (shdrPrg == nullptr) {
        m_shaderProgram = new CommonShader();
        m_shaderProgram->ShaderInit();
    }
    else
        m_shaderProgram = shdrPrg;

    position = params.position;
    size = params.size;
    rotation_angle = params.rotation;

    if (params.file_name == "") params.file_name = DEFAULT_OBSTACLE;
    m_fileName = params.file_name;

    if (loadMultipleMesh() != true) {
        std::cerr << "initializeModels(): Obstacle model loading failed." << std::endl;
    }

   
}

Obstacle::Obstacle(Parameters params, CommonShader* shdrPrg, bool hardcore) {
    if (shdrPrg == nullptr) {
        m_shaderProgram = new CommonShader();
        m_shaderProgram->ShaderInit();
        // initializeShaderProgram();
    }
    else
        m_shaderProgram = shdrPrg;

    position = params.position;
    size = params.size;
    rotation_angle = params.rotation;
    m_fileName = params.file_name;

    loadGeometry();
}


void Obstacle::update(const float elapsedTime, const glm::mat4* parentModelMatrix) {
    return;
}

void Obstacle::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(m_shaderProgram->program);

    // prepare modeling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation_angle), glm::vec3(0, 0, 1));
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
        CHECK_GL_ERROR();

        if (m_fileName == "") {
            glBindTexture(GL_TEXTURE_2D, m_geometry->texture);
            // glBindTexture(GL_TEXTURE_2D, m_geometry->texture2);
            glDrawArrays(GL_TRIANGLES, 0, m_geometry->numTriangles * 3);
        } else 
            glDrawElements(GL_TRIANGLES, m_geometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
        CHECK_GL_ERROR();
    }

    glBindVertexArray(0);
    glUseProgram(0);
}

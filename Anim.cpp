#include "Anim.h"
#include "parameters.h"
#include <iostream>


void Anim::loadGeometry(std::string& name) {
    m_geometry = new ObjectGeometry;

    m_geometry->texture = pgr::createTexture(name);

    glGenVertexArrays(1, &(m_geometry->vertexArrayObject));
        glBindVertexArray(m_geometry->vertexArrayObject);

    glGenBuffers(1, &(m_geometry->vertexBufferObject));
    glBindBuffer(GL_ARRAY_BUFFER, m_geometry->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(animVertexData), animVertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(banner_shader->locations.position);
    glVertexAttribPointer(banner_shader->locations.position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

    glEnableVertexAttribArray(banner_shader->locations.texCoord);
    glVertexAttribPointer(banner_shader->locations.texCoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    m_geometry->ambient = glm::vec3(0.01f);
    m_geometry->diffuse = glm::vec3(0.3f);
    m_geometry->specular = glm::vec3(0.3f);
    m_geometry->shininess = 0.01f;

    glBindVertexArray(0);
    CHECK_GL_ERROR();
    m_geometry->numTriangles = animNumQuadVertices;
}

Anim::Anim(float elapsedTime, const glm::vec3& pos, AnimShader* shdrPrg) {
    if (shdrPrg == nullptr) {
        banner_shader = new AnimShader();
        banner_shader->moving = false;
        if (!banner_shader->ShaderInit())
            std::cout << "ERROR loading banner shader" << std::endl;
    }
    else
        banner_shader = shdrPrg;

    m_shaderProgram = nullptr;

    startTime = elapsedTime;
    currentTime = startTime;

    size = ANIM_SIZE;
    direction = glm::vec3(0.0f, 0.0f, 1.0f);

    frameDuration = 0.1f;

    position = pos;

    rotation_angle = 0.0f;
    time_to_live = 0.0f;
    std::string name = "data/anim.png";
    loadGeometry(name);
}

Anim::Anim(float elapsedTime, AnimShader* shdrPrg, const glm::vec3& pos) {
    banner_shader = shdrPrg;

    m_shaderProgram = nullptr;

    startTime = elapsedTime;
    currentTime = startTime;

    size = ANIM_SIZE;
    direction = glm::vec3(0.0f, 0.0f, 1.0f);

    frameDuration = 0.1f;

    position = pos;

    rotation_angle = 0.0f;
    time_to_live = 1.0f;
    std::string name = "data/coin_anim.png";
    loadGeometry(name);
}

void Anim::update(const float elapsedTime, const glm::mat4* parentModelMatrix) {
    currentTime = elapsedTime;
}

void Anim::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(banner_shader->program);

    // prepare modeling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation_angle), glm::vec3(0, 0, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size, size, size));


    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
    matrix = glm::scale(matrix, glm::vec3(size));

    glm::mat4 PVMmatrix = projectionMatrix * viewMatrix * matrix;

    glUniformMatrix4fv(banner_shader->locations.Vmatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));   // view

    glUniformMatrix4fv(banner_shader->locations.PVMmatrix, 1, GL_FALSE, glm::value_ptr(PVMmatrix)); // model-view-projection


    glUniform1f(banner_shader->locations.time, currentTime - startTime);
    // std::cout << banner_shader->locations.time << std::endl;
    glUniform1i(banner_shader->locations.texSampler, 0);
    // glUniform1f(banner_shader->frameDuration, frameDuration);
    if (time_to_live > 0.0f)
        glUniform1i(banner_shader->hud, 1);
    else
        glUniform1i(banner_shader->hud, 0);

    glBindVertexArray(m_geometry->vertexArrayObject);
    CHECK_GL_ERROR();

    glBindTexture(GL_TEXTURE_2D, m_geometry->texture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_geometry->numTriangles);

    glBindVertexArray(0);
    glUseProgram(0);
    glDisable(GL_BLEND);
}


bool Anim::isDead() {
    if (currentTime - startTime > time_to_live)
        return true;
    return false;
}

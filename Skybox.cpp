#include "Skybox.h"
#include "parameters.h"
#include <iostream>


void Skybox::loadGeometry() {
    m_geometry = new ObjectGeometry;

    // 2D coordinates of 2 triangles covering the whole screen (NDC), draw using triangle strip
    static const float screenCoords[] = {
      -1.0f, -1.0f,
       1.0f, -1.0f,
      -1.0f,  1.0f,
       1.0f,  1.0f
    };

    glGenVertexArrays(1, &(m_geometry->vertexArrayObject));
    glBindVertexArray(m_geometry->vertexArrayObject);

    // buffer for far plane rendering
    glGenBuffers(1, &(m_geometry->vertexBufferObject));
    glBindBuffer(GL_ARRAY_BUFFER, m_geometry->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenCoords), screenCoords, GL_STATIC_DRAW);


    glEnableVertexAttribArray(skybox_shader->screenCoord);
    glVertexAttribPointer(skybox_shader->screenCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
    glUseProgram(0);
    CHECK_GL_ERROR();

    m_geometry->numTriangles = 2;

    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &(m_geometry->texture));
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_geometry->texture);
    CHECK_GL_ERROR();

    const char* suffixes[] = { "px", "nx", "py", "ny", "pz", "nz" };
    // const char* suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
    
    GLuint targets[] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    /*
    GLuint targets[] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    };
    */
    for (int i = 0; i < 6; i++) {
        std::string texName = m_fileName + "_" + suffixes[i] + SKYBOX_FORMAT;
        std::cout << "Loading cube map texture: " << texName << std::endl;
        if (!pgr::loadTexImage2D(texName, targets[i])) {
            pgr::dieWithError("Skybox cube map loading failed!");
        }
    }

    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    CHECK_GL_ERROR();

    // unbind the texture (just in case someone will mess up with texture calls later)
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    CHECK_GL_ERROR();
}

Skybox::Skybox(float elapsedTime, std::string file_name) {
    currentTime = elapsedTime;
    m_fileName = file_name; // texture prefix

    skybox_shader = new SkyboxShader();
    skybox_shader->ShaderInit();

    loadGeometry();
    
    // -------
    m_shaderProgram = nullptr;
}

void Skybox::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {

    glUseProgram(skybox_shader->program);

    // compose transformations
    glm::mat4 matrix = projectionMatrix * viewMatrix;

    // create view rotation matrix by using view matrix with cleared translation
    glm::mat4 viewRotation = viewMatrix;
    viewRotation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // vertex shader will translate screen space coordinates (NDC) using inverse PV matrix
    glm::mat4 inversePVmatrix = glm::inverse(projectionMatrix * viewRotation);

    glUniformMatrix4fv(skybox_shader->inversePVmatrix, 1, GL_FALSE, glm::value_ptr(inversePVmatrix));
    glUniform1i(skybox_shader->skyboxSampler, 0);

    // draw "skybox" rendering 2 triangles covering the far plane
    glBindVertexArray(m_geometry->vertexArrayObject);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_geometry->texture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_geometry->numTriangles + 2);

    glBindVertexArray(0);
    glUseProgram(0);
}

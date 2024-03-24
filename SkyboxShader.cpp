#include "SkyboxShader.h"


bool SkyboxShader::ShaderInit() {
    std::vector<GLuint> shaderList;

    // push vertex shader and fragment shader
    shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "skybox.vert"));
    shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "skybox.frag"));

    // create the program with two shaders
    program = pgr::createProgram(shaderList);

    // handles to vertex attributes locations
    screenCoord = glGetAttribLocation(program, "screenCoord");
    // get uniforms locations
    skyboxSampler = glGetUniformLocation(program, "skyboxSampler");
    inversePVmatrix = glGetUniformLocation(program, "inversePVmatrix");
    return true;
}

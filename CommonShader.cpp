#include "CommonShader.h"
#include "parameters.h"


    // load and compile shader
bool CommonShader::ShaderInit() {

    std::vector<GLuint> shaderList;

    // push vertex shader and fragment shader
    shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "lightingPerVertex.vert"));
    shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "lightingPerVertex.frag"));

    // create the shader program with two shaders
    program = pgr::createProgram(shaderList);

    // get vertex attributes locations, if the shader does not have this uniform -> return -1
    locations.position = glGetAttribLocation(program, "position");
    locations.normal = glGetAttribLocation(program, "normal");
    locations.texCoord = glGetAttribLocation(program, "texCoord");
    // get uniforms locations
    locations.PVMmatrix = glGetUniformLocation(program, "PVMmatrix");
    locations.Vmatrix = glGetUniformLocation(program, "Vmatrix");
    locations.Mmatrix = glGetUniformLocation(program, "Mmatrix");
    locations.normalMatrix = glGetUniformLocation(program, "normalMatrix");
    locations.time = glGetUniformLocation(program, "time");
    // material
    locations.ambient = glGetUniformLocation(program, "material.ambient");
    locations.diffuse = glGetUniformLocation(program, "material.diffuse");
    locations.specular = glGetUniformLocation(program, "material.specular");
    locations.shininess = glGetUniformLocation(program, "material.shininess");
    // texture
    locations.texSampler = glGetUniformLocation(program, "texSampler");
    locations.useTexture = glGetUniformLocation(program, "material.useTexture");
    // reflector
    locations.reflectorPosition = glGetUniformLocation(program, "reflectorPosition");
    locations.reflectorDirection = glGetUniformLocation(program, "reflectorDirection");

    // lamp
    locations.lampPositionLine1 = glGetUniformLocation(program, "lampPositionLine1");
    locations.numOfLine1 = glGetUniformLocation(program, "numOfLine1");
    locations.distanceLine1 = glGetUniformLocation(program, "distanceLine");

    locations.distanceLine1 = glGetUniformLocation(program, "distanceLine");
    locations.lampIntensity = glGetUniformLocation(program, "lampIntensity");
    locations.sunIntensity = glGetUniformLocation(program, "sunIntensity");
    locations.useFog = glGetUniformLocation(program, "useFog");
    locations.carPosition = glGetUniformLocation(program, "carPosition");

    shaderList.clear();
    initialized = true;

    return true;
}


void CommonShader::setTransformUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {

    glm::mat4 PVM = projectionMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(locations.PVMmatrix, 1, GL_FALSE, glm::value_ptr(PVM));

    glUniformMatrix4fv(locations.Vmatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(locations.Mmatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // just take 3x3 rotation part of the modelMatrix
    // we presume the last row contains 0,0,0,1
    const glm::mat4 modelRotationMatrix = glm::mat4(
        modelMatrix[0],
        modelMatrix[1],
        modelMatrix[2],
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelRotationMatrix));

    glUniformMatrix4fv(locations.normalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));  // correct matrix for non-rigid transform

}


void CommonShader::setMaterialUniforms(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess, GLuint texture) {
    glUniform3fv(locations.diffuse, 1, glm::value_ptr(diffuse));  // 2nd parameter must be 1 - it declares number of vectors in the vector array
    glUniform3fv(locations.ambient, 1, glm::value_ptr(ambient));
    glUniform3fv(locations.specular, 1, glm::value_ptr(specular));
    glUniform1f(locations.shininess, shininess);

    if (texture != 0) {
        glUniform1i(locations.useTexture, 1);  // do texture sampling
        glUniform1i(locations.texSampler, 0);  // texturing unit 0 -> samplerID   [for the GPU linker]
        glActiveTexture(GL_TEXTURE0 + 0);                  // texturing unit 0 -> to be bound [for OpenGL BindTexture]
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    else {
        glUniform1i(locations.useTexture, 0);  // do not sample the texture
    }
}


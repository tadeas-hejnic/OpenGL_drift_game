#include "AnimShader.h"


bool AnimShader::ShaderInit() {
	std::vector<GLuint> shaderList;

	std::string shader = "anim";
	if (moving)
		shader = "banner";
	shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, shader + ".vert"));
	shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, shader + ".frag"));

	// create the program with two shaders
	program = pgr::createProgram(shaderList);

	// get position and texture coordinates attributes locations
	locations.position = glGetAttribLocation(program, "position");
	locations.texCoord = glGetAttribLocation(program, "texCoord");
	// get uniforms locations
	locations.PVMmatrix = glGetUniformLocation(program, "PVMmatrix");
	locations.Vmatrix = glGetUniformLocation(program, "Vmatrix");
	locations.time = glGetUniformLocation(program, "time");
	locations.texSampler = glGetUniformLocation(program, "texSampler");

	frameDuration = glGetUniformLocation(program, "frameDuration");

	hud = glGetUniformLocation(program, "hud");

	CHECK_GL_ERROR();

	if (program)
		return true;
	return false;
}

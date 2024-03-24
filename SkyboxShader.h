#pragma once
#include "CommonShader.h"


class SkyboxShader : public CommonShader {
public:
	bool ShaderInit() override;

	GLint screenCoord;
	GLint skyboxSampler;
	GLint inversePVmatrix;
};


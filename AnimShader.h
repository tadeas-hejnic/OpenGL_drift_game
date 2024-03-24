#pragma once
#include "CommonShader.h"


class AnimShader : public CommonShader {
public:
	bool ShaderInit() override;

	GLint frameDuration;

	GLint hud;
	bool moving;
};


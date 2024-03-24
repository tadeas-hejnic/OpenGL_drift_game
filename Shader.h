#pragma once
#include "pgr.h"


class ShaderProgram {
public:
	/// Constructor.
    /**
      Sets the default values and calls the function for loading geometry.
    */
	ShaderProgram() {}
	virtual ~ShaderProgram() = default;

	/// Shader initialization.
    /**
      Based on shader type initialize the shader.
    */
	virtual bool ShaderInit() = 0;

	GLuint program;		///< OpenGL shader program.
	bool initialized;	///< True if the shader was initialized.
};

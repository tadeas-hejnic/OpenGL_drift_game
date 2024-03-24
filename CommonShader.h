//----------------------------------------------------------------------------------------
/**
 * \file       CommonShader.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Common shader
 *
 * This common shader is used for most of the objects in the scene.
*/
//----------------------------------------------------------------------------------------

#ifndef _COMMON_SHADER_H_
#define _COMMON_SHADER_H_

#pragma once
#include "Shader.h"


class CommonShader : public ShaderProgram {
public:
	bool ShaderInit() override;

	/// Set the transform uniforms.
    /**
      Sets the given values to shader uniforms.

      \param[in] modelMatrix        Matrix to be set.
      \param[in] viewMatrix         Matrix to be set.
      \param[in] projectionMatrix   Matrix to be set.
    */
	virtual void setTransformUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

	/// Set the material uniforms.
    /**
      Sets the given values to shader uniforms.

      \param[in] ambient    Material ambient.
      \param[in] diffuse    Material diffuse.
      \param[in] specular   Material specular.
      \param[in] shininess  Material shininess.
      \param[in] texture    Material texture.
    */
	virtual void setMaterialUniforms(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess, GLuint texture);

	/**
	  * \brief Indices of the vertex shader inputs (locations)
	  */
	struct {
		// vertex attributes locations
		GLint position;
		// uniforms locations
		GLint PVMmatrix;
		GLint Vmatrix;
		GLint Mmatrix;
		GLint normalMatrix;

		GLint color;
		GLint normal;
		GLint texCoord;

		GLint time;

		GLint diffuse;    // = -1;
		GLint ambient;    // = -1;
		GLint specular;   // = -1;
		GLint shininess;  // = -1;

		// texture
		GLint useTexture; // = -1; 
		GLint texSampler; // = -1;
		
		// reflector related uniforms
		GLint reflectorPosition;  // = -1; 
		GLint reflectorDirection; // = -1;

		GLint lampPositionLine1;
		GLint numOfLine1;
		GLint distanceLine1;

		GLint lampIntensity;
		GLint sunIntensity;
		GLint useFog;
		GLint carPosition;
	} locations;
};

#endif // _COMMON_SHADER_H_

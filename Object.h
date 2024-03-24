//----------------------------------------------------------------------------------------
/**
 * \file       Object.h
 * \author     Tadeáš Hejnic
 * \date       2023/05/20
 * \brief      Parent object instance
 *
*/
//----------------------------------------------------------------------------------------

#ifndef _OBJECT_H_
#define _OBJECT_H_

#pragma once
#include "CommonShader.h"
#include "pgr.h"


/**
 * \brief Geometry of an object (vertices, triangles).
 */
typedef struct _ObjectGeometry {
	GLuint        vertexBufferObject;   ///< identifier for the vertex buffer object
	GLuint        elementBufferObject;  ///< identifier for the element buffer object
	GLuint        vertexArrayObject;    ///< identifier for the vertex array object
	unsigned int  numTriangles;         ///< number of triangles in the mesh

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	GLuint texture;
} ObjectGeometry;

class ObjectInstance;
/**
 * \brief Linear representation of the scene objects.  The objects themselves may represent the subtrees.
 */
typedef std::vector<ObjectInstance*> ObjectList;

class ObjectInstance {

protected:

	ObjectGeometry * m_geometry;						///< Object single mesh geometry.
	std::vector<ObjectGeometry*> m_multiple_geometry;	///< Object multiple mesh geometry.

	glm::mat4		localModelMatrix;					///< Local model matrix.
	glm::mat4		globalModelMatrix;					///< Global model matrix.

	CommonShader * m_shaderProgram;						///< Shader.
	std::string m_fileName;								///< Name of the model file.

public:

	/// Constructor
	/**
	 * ObjectInstance constructor. Takes a pointer to the shader and must create object resources (VBO and VAO)
	 * \param shdrPrg pointer to the shader program for rendering objects data
	 */
	ObjectInstance(CommonShader * shdrPrg = nullptr) : m_geometry(nullptr), m_shaderProgram(shdrPrg) {}
	virtual ~ObjectInstance();

	/// Update
	/**
	* Recalculates all variables.
	* \param elapsedTime time value in seconds, such as 0.001*glutGet(GLUT_ELAPSED_TIME) (conversion milliseconds => seconds)
	* \param parentModelMatrix parent transformation in the scene-graph subtree
	*/
	virtual void update(const float elapsedTime, const glm::mat4* parentModelMatrix) {
		return;
	}

	/// Draw
	/**
	 * Abstract drawing method.
	 */
	virtual void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;

	/// Mesh loader
	/**
	 * Loads single mesh from file_name.
	 */
	bool loadSingleMesh();

	/// Mesh loader
	/**
	 * Loads multiple mesh from file_name.
	 */
	bool loadMultipleMesh();
};

#endif // _OBJECT_H_

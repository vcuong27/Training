#pragma once
#include "Vertex.h"
#include "GameConfig.h"

class Models
{
private:
	GLuint		m_iModelID;
	GLuint		m_iNumIndices;
	GLuint		m_iVboID; 
	GLuint		m_iIboID;
public:
	Models(const std::string& fileName, GLuint type);
	~Models();
	GLuint		GetVertexObject();
	GLuint		GetIndiceObject();
	GLuint		GetNumIndiceObject();
	void		SetModelId(GLuint);
	GLuint		GetModelId();
};
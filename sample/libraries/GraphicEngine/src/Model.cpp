#include "Model.h"
#include "utils\FileUtils.h"
#include "Vertex.h"
#include <sstream>

const GLuint Model::MODEL_TYPE_NFG = 111;

Model* Model::createWithFiles	(const std::string& vsFile, GLuint type)
{
	auto model = new Model();

	if (model && model->initWithFiles(vsFile, type))
	{
		return model;
	}

	delete model;
	model = 0;

	return nullptr;
}

bool Model::initWithFiles	(const std::string& vsFile, GLuint type)
{
	std::string strData = FileUtils::getInstance()->getFileContentText(vsFile);

	if(strData == "")
		return false;

	std::stringstream ss;
	ss << strData;

	GLuint iNumVertex;
	Vertex *verticesData;
	GLuint *Indices;

	//only one type
	//if(type == MODEL_TYPE_NFG)
	{
		std::string lines;
		
		GLuint line=0, iTemp=0;
		std::getline(ss, lines);
		sscanf(lines.c_str(), "NrVertices: %d", &iNumVertex);
		verticesData	= new Vertex[iNumVertex];
		for(GLuint i=0;i<iNumVertex;i++)
		{
			std::getline(ss, lines);
			sscanf(lines.c_str(), "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
				&line,
				&verticesData[i].position.x,	&verticesData[i].position.y,	&verticesData[i].position.z,
				&verticesData[i].normal.x,		&verticesData[i].normal.y,		&verticesData[i].normal.z,
				&verticesData[i].bitangent.x,	&verticesData[i].bitangent.y,	&verticesData[i].bitangent.z,
				&verticesData[i].tangent.x,		&verticesData[i].tangent.y,		&verticesData[i].tangent.z,
				&verticesData[i].uv.x,			&verticesData[i].uv.y);
		}

		std::getline(ss, lines);
		sscanf(lines.c_str(), "\nNrIndices: %d",&_iNumIndices);
		Indices			= new GLuint[_iNumIndices];
		for(GLuint i=0; i<_iNumIndices/3; i++)
		{
			std::getline(ss, lines);
			sscanf(lines.c_str(), "%d.    %d,    %d,    %d",&line, &Indices[3*i+0], &Indices[3*i+1], &Indices[3*i+2]);
		}
	}

	glGenBuffers(1, &_iVboID);
	glBindBuffer(GL_ARRAY_BUFFER, _iVboID);
	glBufferData(GL_ARRAY_BUFFER, iNumVertex* sizeof(Vertex), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &_iIboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iIboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,_iNumIndices *sizeof(GLuint), Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete [] verticesData;
	delete [] Indices;
	return true;
}



GLuint Model::GetVertexObject(){return _iVboID;}
GLuint Model::GetIndiceObject(){return _iIboID;}
GLuint Model::GetNumIndiceObject(){return _iNumIndices;}
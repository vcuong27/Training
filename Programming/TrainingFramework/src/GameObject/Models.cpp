#include "Models.h"
#include "utilities.h" 


void Models::Filter(unsigned char* pBuffer, GLint range)
{
	unsigned char* pTemp = new unsigned char[range * range];
	GLfloat fAvg, fNum;
	GLint ii, jj;
	for (GLint i = 0; i < range; i++)
	{
		for (GLint j = 0; j < range; j++)
		{
			fAvg = 0.0;
			fNum = 0.0;
			for (ii = i - 1; ii <= i + 1; ii++)
			{
				for (jj = j - 1; jj <= j + 1; jj++)
				{
					if ((ii < 0) || (ii >= range) || (jj < 0) || (jj > range)) continue;
					fNum += 1.0;
					fAvg += pBuffer[ii * range + jj];
				}
			}
			pTemp[i * range + j] = (unsigned char)(fAvg / fNum);
		}
	}
	memcpy(pBuffer, pTemp, range * range);
	delete[]pTemp;
}

int Models::Init(const char* szFileName, GLuint type)
{

	std::ifstream modelFile(szFileName, std::ios::binary);
	if (!modelFile.is_open())
	{
		LOGE("ERROR %s \n", szFileName);
		return 0;
	}
	LOGI("Load Models:%s\t\t", szFileName);

	GLuint iNumVertex = 0;
	Vertex* verticesData;
	GLuint* Indices;
	if (type == NFG)
	{
		char* buffer;
		std::string strtmp;
		float posX, posY, posZ, normX, normY, normZ, binormX, binormY, binormZ, tgtX, tgtY, tgtZ, uvX, uvY;
		//read data from file
		modelFile.seekg(0, modelFile.end);
		size_t bufSize = modelFile.tellg();
		modelFile.seekg(0, modelFile.beg);

		buffer = new char[bufSize + 1];
		modelFile.read(buffer, bufSize);

		buffer[bufSize] = '\0';
		std::stringstream ss(buffer);

		std::getline(ss, strtmp, '\n');
		int rs = sscanf(strtmp.c_str(), "NrVertices: %d", &iNumVertex);
		verticesData = new Vertex[iNumVertex];
		for (GLuint i = 0; i < iNumVertex; i++)
		{
			std::getline(ss, strtmp, '\n');
			rs = sscanf(strtmp.c_str(), "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &posX, &posY, &posZ, &normX, &normY, &normZ, &binormX, &binormY, &binormZ, &tgtX, &tgtY, &tgtZ, &uvX, &uvY);
			verticesData[i].position.x = posX;
			verticesData[i].position.y = posY;
			verticesData[i].position.z = posZ;

			verticesData[i].normal.x = normX;
			verticesData[i].normal.y = normY;
			verticesData[i].normal.z = normZ;

			verticesData[i].bitangent.x = binormX;
			verticesData[i].bitangent.y = binormY;
			verticesData[i].bitangent.z = binormZ;

			verticesData[i].tangent.x = binormX;
			verticesData[i].tangent.y = binormY;
			verticesData[i].tangent.z = binormZ;

			verticesData[i].uv.x = uvX;
			verticesData[i].uv.y = uvY;
		}
		std::getline(ss, strtmp, '\n');

		rs = sscanf(strtmp.c_str(), "NrIndices: %d", &m_iNumIndices);
		Indices = new GLuint[m_iNumIndices];
		GLuint a, b, c;
		for (GLuint i = 0; i < m_iNumIndices / 3; i++)
		{
			std::getline(ss, strtmp, '\n');
			rs = sscanf(strtmp.c_str(), " %*d.  %d,  %d,  %d", &a, &b, &c);
			Indices[3 * i + 0] = a;
			Indices[3 * i + 1] = b;
			Indices[3 * i + 2] = c;
		}
	}

	//buffer object
	glGenBuffers(1, &m_iVboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVboID);
	glBufferData(GL_ARRAY_BUFFER, iNumVertex * sizeof(Vertex), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//if(m_iIboID == 0)
	{
		glGenBuffers(1, &m_iIboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iNumIndices * sizeof(GLuint), Indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	modelFile.close();
	LOGI("Done.\n");
	return 0;
}

int Models::Init(GLuint type)
{
	GLuint iNumVertex = 0;
	Vertex* verticesData;
	GLuint* Indices;
	if (type == GAME_3D_SPRITE)
	{
		//gen model
		iNumVertex = 8;
		verticesData = new Vertex[iNumVertex];
		int ii = 0;
		float ratio = 1;
		float r = 1;
		float angle = 0;
		float height = -1.0;
		//A
		verticesData[ii].position.x = 1;
		verticesData[ii].position.y = 1;
		verticesData[ii].position.z = 1;
		verticesData[ii].uv.x = 0.0;
		verticesData[ii].uv.y = 0.0;
		ii++;
		//B
		verticesData[ii].position.x = -1;
		verticesData[ii].position.y = 1;
		verticesData[ii].position.z = 1;
		verticesData[ii].uv.x = 0.0;
		verticesData[ii].uv.y = 0.0;
		ii++;
		//C
		verticesData[ii].position.x = -1;
		verticesData[ii].position.y = 1;
		verticesData[ii].position.z = -1;
		verticesData[ii].uv.x = 0.0;
		verticesData[ii].uv.y = 0.0;
		ii++;
		//D
		verticesData[ii].position.x = 1;
		verticesData[ii].position.y = 1;
		verticesData[ii].position.z = -1;
		verticesData[ii].uv.x = 0.0;
		verticesData[ii].uv.y = 0.0;
		ii++;

		//A
		verticesData[ii].position.x = 1;
		verticesData[ii].position.y = -1;
		verticesData[ii].position.z = 1;
		verticesData[ii].uv.x = 0.0;
		verticesData[ii].uv.y = 0.0;
		ii++;
		//B
		verticesData[ii].position.x = -1;
		verticesData[ii].position.y = -1;
		verticesData[ii].position.z = 1;
		verticesData[ii].uv.x = 0.0;
		verticesData[ii].uv.y = 0.0;
		ii++;
		//C
		verticesData[ii].position.x = -1;
		verticesData[ii].position.y = -1;
		verticesData[ii].position.z = -1;
		verticesData[ii].uv.x = 0.0;
		verticesData[ii].uv.y = 0.0;
		ii++;
		//D
		verticesData[ii].position.x = 1;
		verticesData[ii].position.y = -1;
		verticesData[ii].position.z = -1;
		verticesData[ii].uv.x = 0.0;
		verticesData[ii].uv.y = 0.0;
		ii++;

		ii = 0;
		m_iNumIndices = 36;
		Indices = new GLuint[m_iNumIndices];
		for (GLuint i = 0; i < m_iNumIndices; i++)
		{
			Indices[i] = 0;
		}
		Indices[ii] = 0; ii++;
		Indices[ii] = 1; ii++;
		Indices[ii] = 5; ii++;

		Indices[ii] = 0; ii++;
		Indices[ii] = 1; ii++;
		Indices[ii] = 2; ii++;

		Indices[ii] = 0; ii++;
		Indices[ii] = 5; ii++;
		Indices[ii] = 4; ii++;

		Indices[ii] = 0; ii++;
		Indices[ii] = 2; ii++;
		Indices[ii] = 3; ii++;

		Indices[ii] = 0; ii++;
		Indices[ii] = 3; ii++;
		Indices[ii] = 7; ii++;

		Indices[ii] = 0; ii++;
		Indices[ii] = 7; ii++;
		Indices[ii] = 4; ii++;

		Indices[ii] = 6; ii++;
		Indices[ii] = 5; ii++;
		Indices[ii] = 1; ii++;

		Indices[ii] = 6; ii++;
		Indices[ii] = 7; ii++;
		Indices[ii] = 3; ii++;

		Indices[ii] = 6; ii++;
		Indices[ii] = 5; ii++;
		Indices[ii] = 4; ii++;

		Indices[ii] = 6; ii++;
		Indices[ii] = 1; ii++;
		Indices[ii] = 2; ii++;

		Indices[ii] = 6; ii++;
		Indices[ii] = 3; ii++;
		Indices[ii] = 2; ii++;

		Indices[ii] = 6; ii++;
		Indices[ii] = 4; ii++;
		Indices[ii] = 7; ii++;
	}

	if (type == GAME_2D_SPRITE)
	{
		iNumVertex = 4;
		verticesData = new Vertex[iNumVertex];

		int ii = 0;
		verticesData[ii].position = Vector3(0.0, 0.0, 0.0);
		verticesData[ii].uv = Vector2(0.0, 1.0);
		ii++;

		verticesData[ii].position = Vector3(0.0, 1.0, 0.0);
		verticesData[ii].uv = Vector2(0.0, 0.0);
		ii++;

		verticesData[ii].position = Vector3(1.0, 1.0, 0.0);
		verticesData[ii].uv = Vector2(1.0, 0.0);
		ii++;

		verticesData[ii].position = Vector3(1.0, 0.0, 0.0);
		verticesData[ii].uv = Vector2(1.0, 1.0);



		m_iNumIndices = 6;
		Indices = new GLuint[m_iNumIndices];
		ii = 0;
		Indices[ii] = 0; ii++;
		Indices[ii] = 1; ii++;
		Indices[ii] = 2; ii++;

		Indices[ii] = 0; ii++;
		Indices[ii] = 2; ii++;
		Indices[ii] = 3; ii++;
	}


	//buffer object
	glGenBuffers(1, &m_iVboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVboID);
	glBufferData(GL_ARRAY_BUFFER, iNumVertex * sizeof(Vertex), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//if(m_iIboID == 0)
	{
		glGenBuffers(1, &m_iIboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iNumIndices * sizeof(GLuint), Indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	delete[] verticesData;
	delete[] Indices;
	LOGI("Done.\n");
	return 0;
}

GLuint Models::GetVertexObject() { return m_iVboID; }
GLuint Models::GetIndiceObject() { return m_iIboID; }
GLuint Models::GetNumIndiceObject() { return m_iNumIndices; }
void Models::SetModelId(GLuint id) { m_iModelID = id; }
GLuint Models::GetModelId() { return m_iModelID; }
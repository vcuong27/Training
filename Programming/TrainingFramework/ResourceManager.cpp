#include "stdafx.h"
#include "ResourceManager.h"

#include "Models.h"
#include "Shaders.h"
#include "Texture.h"


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for(GLuint i=0;i<m_iNum2DTex;i++)
		delete m_2DTextures[i];
	for(GLuint i=0;i<m_iNumModel;i++)
		delete m_Models[i];
	for(GLuint i=0;i<m_iNumShader;i++)
		delete m_Shaders[i];
	delete [] m_Models;
	delete [] m_Shaders;
	delete [] m_2DTextures;
}

void ResourceManager::Init(const char *szFileName)
{
	#ifdef WIN32
	FILE * f;
	fopen_s(&f, szFileName, "rb" );
	printf_s("Read ResourceManager file:%s\n",szFileName);
#else
	FILE *f = fopen(szFileName, "rb" );
	
	if(f==NULL) LOGE("Fail RM"); 
#endif //android

	GLuint tiling,ID,iTypeModel;
	GLuint i,j, state,lenstr;

	char *s=new char[255];
	char *strS1=new char[255];
	char *strS2=new char[255];
	char c='0';

	//read models
	FSCANF(f,"%s",s);
	FSCANF(f,"%d",&m_iNumModel);
	m_iNumModel++;
	m_iNumModel++;

	m_Models= new Models*[m_iNumModel];
	m_Models[0]=new Models();
	m_Models[0]->Init(GAME_OBJ);
	m_Models[0]->SetModelId(0);

	m_Models[1]=new Models();
	m_Models[1]->Init(GAME_BUTTON);
	m_Models[1]->SetModelId(1);

	for(i=2;i<m_iNumModel;i++)
	{
		FSCANF(f,"%s",s);FSCANF(f,"%d",&ID);
		FSCANF(f,"%s",s);
		FSCANF(f,"%s",s);	
		lenstr=strlen(s);
		memcpy(strS1,s+1,lenstr-1);
		strS1[lenstr-2]=0;

		FSCANF(f,"%s",s);
		FSCANF(f,"%s",s);
		iTypeModel=NFG;
		if(strcmp(s,"RAW")==0) iTypeModel=RAW;
		if(strcmp(s,"NONE")==0) iTypeModel=NONE;
		m_Models[i]=new Models();
		m_Models[i]->Init(strS1,iTypeModel);
		m_Models[i]->SetModelId(ID);
	}

	//read 2D textures
	FSCANF(f,"%s",s);
	FSCANF(f,"%s",s);
	FSCANF(f,"%d",&m_iNum2DTex);
	m_2DTextures= new Texture*[m_iNum2DTex];

	for(i=0;i<m_iNum2DTex;i++)
	{
		FSCANF(f,"%s",s);FSCANF(f,"%d",&ID);
		FSCANF(f,"%s",s);
		//file
		FSCANF(f,"%s",s);	
		lenstr=strlen(s);
		memcpy(strS1,s+1,lenstr-1);
		strS1[lenstr-2]=0;
		//tilling
		FSCANF(f,"%s",s);	
		FSCANF(f,"%s",s);
		tiling=GL_CLAMP_TO_EDGE;
		if(strcmp("CLAMP",s)==0) tiling=GL_CLAMP_TO_EDGE;
		if(strcmp("REPEAT",s)==0) tiling=GL_REPEAT;
		m_2DTextures[i]=new Texture();
		m_2DTextures[i]->Init(strS1,tiling,GL_LINEAR_MIPMAP_LINEAR);
		m_2DTextures[i]->Set2DTextureId(ID);
	}

	//read shaders
	FSCANF(f,"%s",s);
	FSCANF(f,"%d",&m_iNumShader);
	m_Shaders=new Shaders*[m_iNumShader];
	for(i=0;i<m_iNumShader;i++)
	{
		FSCANF(f,"%s",s);FSCANF(f,"%d",&ID);
		FSCANF(f,"%s",s);
		//file
		FSCANF(f,"%s",s);	
		lenstr=strlen(s);
		memcpy(strS1,s+1,lenstr-1);
		strS1[lenstr-2]=0;
		//file
		FSCANF(f,"%s",s);	
		FSCANF(f,"%s",s);	
		lenstr=strlen(s);
		memcpy(strS2,s+1,lenstr-1);
		strS2[lenstr-2]=0;
		//state
		FSCANF(f,"%s",s);
		FSCANF(f,"%d",&state);
		m_Shaders[i]=new Shaders();
		m_Shaders[i]->Init(strS1,strS2);
		m_Shaders[i]->SetShaderID(ID);
		for(j=0;j<state;j++)
		{
			FSCANF(f,"%s",s);	
			FSCANF(f,"%s",s);
			if(strcmp("DEPTH_TEST",s)==0) m_Shaders[i]->EnableTest(GL_DEPTH_TEST);
			if(strcmp("CULLING",s)==0) m_Shaders[i]->EnableTest(GL_CULL_FACE);
			if(strcmp("ALPHA",s)==0) m_Shaders[i]->EnableAlpha();
		}
	}

	fclose(f);
	delete[]s;
	delete[]strS1;
	delete[]strS2;
	LOGI("SUCCESS !\n\n");

}

Models* ResourceManager::GetModels(GLuint index)
{
	for(GLuint i=0;i<m_iNumModel;i++)
	{
		if(m_Models[i]->GetModelId() ==index)
			return m_Models[i];
	}
	return NULL;
}

Texture* ResourceManager::GetTexture(GLuint index)
{
	for(GLuint i=0;i<m_iNum2DTex;i++)
	{
		if(m_2DTextures[i]->Get2DTextureId() ==index)
			return m_2DTextures[i];
	}
	return NULL;
}

Shaders* ResourceManager::GetShaders(GLuint index)
{
	for(GLuint i=0;i<m_iNumShader;i++)
	{
		if(m_Shaders[i]->GetShaderID() ==index)
			return m_Shaders[i];
	}
	return NULL;
}

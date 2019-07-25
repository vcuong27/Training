#include "Texture.h"
#include "utils\FileUtils.h"

Texture* Texture::createWithFiles	(const std::string& vsFile, GLuint wapMode,GLuint filterMode)
{
	auto texture = new Texture();

	if (texture && texture->initWithFiles(vsFile, wapMode, filterMode))
	{
		return texture;
	}

	delete texture;
	texture = 0;

	return nullptr;
}
bool Texture::initWithFiles	(const std::string& vsFile, GLuint wapMode,GLuint filterMode)
{
	glGenTextures(1,&m_iTextGlId);
	glBindTexture(GL_TEXTURE_2D,m_iTextGlId);

	GLint h,w,bpp;
	char *imageData = FileUtils::getInstance()->LoadTGA(vsFile,&w,&h,&bpp);
	if(imageData == 0)
	{
		return 0;
	}
	switch (bpp)
	{
	case 24:
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,imageData);
		break;
	case 32:
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,imageData);
		break;
	}

	if(imageData!=0) delete [] imageData;

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wapMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wapMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filterMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filterMode);

	if((filterMode== GL_LINEAR_MIPMAP_LINEAR)||(filterMode== GL_LINEAR_MIPMAP_NEAREST)|| (filterMode== GL_NEAREST_MIPMAP_LINEAR)||(filterMode== GL_NEAREST_MIPMAP_NEAREST))
		glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,0);
	return true;
}

GLuint Texture::Get2DTextureAdd()
{
	return m_iTextGlId;
}
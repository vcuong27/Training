#include "Sprite.h"
#include "Vertex.h"


Sprite::Sprite(SceneNode * parent) : SceneNode(parent)
{

	//_texture = Texture::createWithFiles("Textures/avatar_1.tga"); //TODO: unhardcode texture filepath
}

Sprite::~Sprite()
{
	//no need to delete texutre
}

void Sprite::draw()
{
	if ( !isVisible() )
		return;

	_shaderProgram->use();

	glBindBuffer(GL_ARRAY_BUFFER, _rectModel->GetVertexObject());

	GLint a_pos = _shaderProgram->getAttribute(GLProgram::ATTRIBUTE_POSITION);

	if (a_pos != -1)
	{
		glEnableVertexAttribArray(a_pos);
		glVertexAttribPointer(a_pos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	GLint a_uv = _shaderProgram->getAttribute("a_uv"); //TODO: unhardcode this
	if (a_uv != -1)
	{
		glEnableVertexAttribArray(a_uv);
		glVertexAttribPointer(a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(Vector3) * 4));
	}

	GLint u_texture = _shaderProgram->getUniform("u_texture"); //TODO: unhardcode this
	if (u_texture != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture->Get2DTextureAdd());
		glUniform1i(u_texture, 0);
	}

	GLint u_world = _shaderProgram->getUniform("u_world");
	if (u_world != -1)
	{
		glUniformMatrix4fv(u_world, 1, GL_FALSE, (float*)(_worldMatrix.m));
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rectModel->GetIndiceObject());
	glDrawElements(GL_TRIANGLES, _rectModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	SceneNode::draw();
}

void Sprite::update(float dt)
{
	//int a = 0;
	SceneNode::update(dt);
}

/*
bool Sprite::init()
{
	if (!SceneNode::init())
	{
		return false;
	}

	//_shaderProgram = GLProgram::createWithFiles("Shaders/rect.vs", "Shaders/rect.fs");
	//_rectModel = Model::createWithFiles("Models/Rect.nfg", Model::MODEL_TYPE_NFG);
	//_texture = Texture::createWithFiles("Textures/avatar_1.tga"); //TODO: unhardcode texture filepath

	return true;
}*/

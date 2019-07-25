#include "SpriteSheet.h"
#include "Vertex.h"

SpriteSheet::SpriteSheet(SceneNode* parent, Vector2& size , Vector2& spriteSize): SceneNode(parent),
mDelay(0.0f),
mTimer(0.0f),
mSize(size),
mSpriteSize(spriteSize),
mCurrentPos(0)
{
	mRow = (int)(size.y / spriteSize.y);
	mCloumn = (int)(size.x / spriteSize.x);
	mCount = mRow * mCloumn;
}

void SpriteSheet::ResetSpriteSheet()
{
	mTimer = 0.0f;
	mCurrentPos = 0;
}

void SpriteSheet::draw() {
	if ( !isVisible() )
		return;

	_shaderProgram->use();
	//glEnable(GL_DEPTH_TEST);
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

	GLint u_data = _shaderProgram->getUniform("u_data"); 
	if (u_data != -1)
	{
		//mRow, mCloumn
		Vector2 data(mRow, mCloumn);
		glUniform2fv(u_data , 1 , (GLfloat *)(&data) );
	}

	GLint u_pos = _shaderProgram->getUniform("u_pos"); 
	if (u_pos != -1)
	{
		//mRow, mCloumn
		int column = mCurrentPos % mCloumn;
		int row = mCurrentPos / mCloumn;
		Vector2 data(row, column);
		glUniform2fv(u_pos , 1 , (GLfloat *)(&data) );
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
	//glDisable(GL_DEPTH_TEST);
	SceneNode::draw();
}
void SpriteSheet::update(float dt) {
	//create correct uv for texture

	if (mCurrentPos == (mCount - 1) && mTimer > mDelay)
	{
		mCurrentPos = 0;
		mTimer = 0.0f;
	}
	else if (mTimer > mDelay)
	{
		mCurrentPos ++;
		mTimer = 0.0f;
	}
	else
	{
		mTimer += dt;
	}
}


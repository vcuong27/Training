#include "Button.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"

extern GLint screenWidth;
extern GLint screenHeight;

Button::Button(void)
{
	Set3DScale(Vector3( 0.5, 0.15, 1));
	Set3DPosition(Vector3(-1,-1,0));
	m_isHandle = false;
}


Button::~Button(void)
{
}

void Button::Init()
{
	m_iHeight	= screenHeight/15;
	m_iWidth	= screenWidth/4;
	Matrix m_Sc, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	m_T.SetTranslation(m_Vec3Position);
	m_WorldMat=m_Sc*m_T;
}

void Button::Draw()
{
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP=m_WorldMat;//* m_pCamera->GetLookAtCamera();

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
	if(m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);


	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if(iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION );
	}

	iTempShaderVaribleGLID =m_pShader->GetAttribLocation((char*) "a_uv");
	if(iTempShaderVaribleGLID !=-1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE,  sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if(iTempShaderVaribleGLID !=-1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1,GL_FALSE,matrixWVP.m[0]);

	
	glDrawElements(GL_TRIANGLES,m_pModel->GetNumIndiceObject(),GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

void Button::Update(GLfloat deltatime)
{
}

void Button::HandleTouchEvents(GameStateMachine* game, GLint x, GLint y, bool bIsPressed)
{
	if((x > m_Vec2DPos.x + 10) && (x < m_Vec2DPos.x + m_iWidth +10) && (y > m_Vec2DPos.y - m_iHeight/2 ) && (y < m_Vec2DPos.y +m_iHeight/2))
	{
			pBtClick(game);
			m_isHandle = true;
	}
}


void Button::SetText(std::string text)
{
	m_Text = text;
}

std::string Button::GetText()
{
	return m_Text;
}

void Button::Set2DPosition(GLfloat x, GLfloat y)
{
	m_Vec2DPos.x	= x;
	m_Vec2DPos.y	= y;
	
	float xx = (2.0*x)/screenWidth - 1.0;
	float yy =  1.0 - (2.0*y)/screenHeight ;
	Set3DPosition(Vector3(xx , yy, 1.0));
	
	Matrix m_Sc, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	m_T.SetTranslation(m_Vec3Position);
	m_WorldMat=m_Sc*m_T;
}

void Button::Set2DPosition(Vector2 pos)
{
	m_Vec2DPos = pos;

}

Vector2 Button::Get2DPosition()
{
	return m_Vec2DPos;
}

void Button::SetTexture(Texture* texture)
{
	m_pTexture = texture;
}

void Button::SetOnClick(void	(*BtClick)(GameStateMachine* game))
{
	pBtClick = BtClick;
}

void Button::SetSize(GLint width, GLint height)
{
	m_iWidth	= width;
	m_iHeight	= height;
}

bool Button::IsHandle()
{
	return m_isHandle;
}
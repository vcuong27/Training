#include "GameObject.h"
#include "Camera.h"
#include "Shaders.h"
#include "Models.h"


GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
}


void GameObject::Init()
{
	Matrix m_Sc, m_Rx, m_Ry, m_Rz, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	GLfloat tempX=(GLfloat)(m_Vec3Rotation.x*PI*2/MAX_DEGREE);
	m_Rx.SetRotationX(tempX);
	GLfloat tempY=(GLfloat)(m_Vec3Rotation.y*PI*2/MAX_DEGREE);
	m_Ry.SetRotationY(tempY);
	GLfloat tempZ=(GLfloat)(m_Vec3Rotation.z*PI*2/MAX_DEGREE);
	m_Rz.SetRotationZ(tempZ);
	m_T.SetTranslation(m_Vec3Position);

	m_WorldMat=m_Sc*m_Rz*m_Rx*m_Ry*m_T;

	//init color
#ifdef ANDROID
	float div = 10000000000.0;
#else
	float div = 100000.0;
#endif

	float add = 0.1f;
	m_Color.x = add + rand () / div;
	m_Color.y = add + rand () / div;
	m_Color.z = add + rand () / div;
	m_Color.w = 1.0f;

}

void GameObject::Draw()
{
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());
	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;
	
	// All object
	matrixWVP = m_WorldMat* m_pCamera->GetLookAtCamera();
	
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if(iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0 );
	}

	iTempShaderVaribleGLID =m_pShader->GetUniformLocation((char*)"u_alpha");
	if(iTempShaderVaribleGLID !=-1)
		glUniform1f(iTempShaderVaribleGLID,1.0);
	
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if(iTempShaderVaribleGLID !=-1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1,GL_FALSE,matrixWVP.m[0]);
		
	
	iTempShaderVaribleGLID =m_pShader->GetUniformLocation((char*)"u_color");
	if(iTempShaderVaribleGLID !=-1)
		glUniform4f(iTempShaderVaribleGLID,m_Color.x,m_Color.y,m_Color.z,m_Color.w);

	glDrawElements(GL_TRIANGLES,m_pModel->GetNumIndiceObject(),GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameObject::Update(GLfloat deltatime)
{

}


void GameObject::Set2DPosition(GLfloat x, GLfloat y)
{
	if(x < 0) x += MAX_COL;
	else if(x >= MAX_COL) x -= MAX_COL;
		

	m_Vec2DPos.x=x;
	m_Vec2DPos.y=y;

	m_Vec3Position.y = MAX_ROW - y;

	/*Matrix rY;
	rY.SetRotationY(x * COLUMN);
	Vector4 pos= Vector4(m_Vec3Position.x,m_Vec3Position.y,m_Vec3Position.z,1.0);
	Vector4 temp= pos* rY;
	/*m_Vec3Position.x=temp.x;
	m_Vec3Position.y=temp.y;
	m_Vec3Position.z=temp.z;*/

	Matrix m_Sc, m_Rx, m_Ry, m_Rz, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	//GLfloat tempX=(GLfloat)(m_Vec3Rotation.x);
	//m_Rx.SetRotationX(tempX);
	GLfloat tempY=(GLfloat)(m_Vec3Rotation.y + x*COLUMN);
	m_Ry.SetRotationY(tempY);
	//GLfloat tempZ=(GLfloat)(m_Vec3Rotation.z);
	//m_Rz.SetRotationZ(tempZ);
	m_T.SetTranslation(m_Vec3Position.x,m_Vec3Position.y,m_Vec3Position.z);

	m_WorldMat=m_Sc*m_Ry*m_T;
	

	/*m_WorldMat.SetIdentity();
	m_WorldMat.Multi(m_Sc);
	//m_WorldMat.Multi(m_Rz);
	//m_WorldMat.Multi(m_Rx);
	m_WorldMat.Multi(m_Ry);
	m_WorldMat.Multi(m_T);*/
}

void GameObject::Set2DPosition(Vector2 pos)
{
	m_Vec2DPos = pos;

}

Vector2 GameObject::Get2DPosition()
{
	return m_Vec2DPos;
}



void GameObject::SetColor(Vector4 color)
{
	m_Color =  color;
}


#include "Sprite3D.h"
#include "Camera.h"
#include "Shaders.h"
#include "Models.h"
#include "Texture.h"


Sprite3D::Sprite3D(void)
{
}


Sprite3D::~Sprite3D(void)
{
}


void Sprite3D::Init()
{
	Matrix m_Sc, m_Rx, m_Ry, m_Rz, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	GLfloat tempX = (GLfloat)(m_Vec3Rotation.x*PI * 2 / MAX_DEGREE);
	m_Rx.SetRotationX(tempX);
	GLfloat tempY = (GLfloat)(m_Vec3Rotation.y*PI * 2 / MAX_DEGREE);
	m_Ry.SetRotationY(tempY);
	GLfloat tempZ = (GLfloat)(m_Vec3Rotation.z*PI * 2 / MAX_DEGREE);
	m_Rz.SetRotationZ(tempZ);
	m_T.SetTranslation(m_Vec3Position);

	m_WorldMat = m_Sc*m_Rz*m_Rx*m_Ry*m_T;


}

void Sprite3D::Draw()
{
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());
	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	// All object
	matrixWVP = m_WorldMat* m_pCamera->GetLookAtCamera();

	if (m_texture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}

	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	}

	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);

	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);


	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
	if (iTempShaderVaribleGLID != -1)
		glUniform4f(iTempShaderVaribleGLID, m_Color.x, m_Color.y, m_Color.z, m_Color.w);

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite3D::Update(GLfloat deltatime)
{

}


void Sprite3D::SetColor(Vector4 color)
{
	m_Color = color;
}


#include "Application.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
extern GLint screenWidth;
extern GLint screenHeight;

Application::Application(void)
{
}


Application::~Application(void)
{
}


void Application::Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	Shaders		*m_Shaders;
	Texture		*m_texture;
	Models		*m_model;
	Camera   *m_Camera;

	m_Shaders = new Shaders();
	m_Shaders->Init("..\\Data\\Shaders\\2DShaderVS.vs", "..\\Data\\Shaders\\2DShaderFS.fs");


	m_texture = new Texture();
	m_texture->Init("..\\Data\\Textures\\btPlay.tga", GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);

	m_model = new Models();
	m_model->Init(GAME_2D_SPRITE);

	GLint dHeight = screenHeight / 8;
	GLint iCenterWidth = screenWidth / 2 - screenWidth / 8;

	m_Sprite2D = new Sprite2D();
	m_Sprite2D->SetShaders(m_Shaders);
	m_Sprite2D->SetModels(m_model);
	m_Sprite2D->SetTexture(m_texture);
	m_Sprite2D->Set2DPosition(iCenterWidth, dHeight);
	m_Sprite2D->Init();

	Vector3 CameraPos(0, 10, 30);
	Vector3 TargetPos(0, 6, 0);
	float fFovY = 0.7f;
	m_Camera = new Camera();
	m_Camera->Init(CameraPos, TargetPos, fFovY, (GLfloat)screenWidth / screenHeight, 1.0f, 5000.0f, 1.0f);

	m_Shaders = new Shaders();
	m_Shaders->Init("..\\Data\\Shaders\\3DShaderVS.vs", "..\\Data\\Shaders\\3DShaderFS.fs");


	m_texture = new Texture();
	m_texture->Init("..\\Data\\Textures\\btPlay.tga", GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);

	m_model = new Models();
	m_model->Init(GAME_3D_SPRITE);

	m_Sprite3D = new Sprite3D();
	m_Sprite3D->SetShaders(m_Shaders);
	m_Sprite3D->SetModels(m_model);
	m_Sprite3D->SetColor(Vector4(0.0, 0.0, 1.0, 0.5));
	m_Sprite3D->SetCamera(m_Camera);
	m_Sprite3D->Init();
}

void Application::Update(GLfloat deltaTime)
{
	//update
	m_Sprite3D->Update(deltaTime);
	m_Sprite2D->Update(deltaTime);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Draw();
	m_Sprite3D->Draw();
	m_Sprite2D->Draw();
}

void Application::HandleKeyEvent(unsigned char key, bool bIsPresseded)
{

}

void Application::HandleTouchEvent(GLint x, GLint y, bool bIsPresseded)
{
}

void Application::Exit()
{
	exit(0);
}

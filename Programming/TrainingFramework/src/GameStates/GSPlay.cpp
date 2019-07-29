#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameManager/ResourceManagers.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	//Init game play
	std::shared_ptr<Shaders> m_Shaders;
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr<Models> m_model;
	std::shared_ptr<Camera> m_Camera;

	//button
	m_Shaders = std::make_shared<Shaders>();
	m_Shaders->Init("..\\Data\\Shaders\\TextureShader.vs", "..\\Data\\Shaders\\TextureShader.fs");

	m_texture = std::make_shared< Texture>();
	m_texture->Init("..\\Data\\Textures\\btPlay.tga", GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);

	m_model = std::make_shared< Models>("..\\Data\\Model\\Sprite2D.nfg", NFG);

	m_Sprite2D = std::make_shared< Sprite2D>(m_model, m_Shaders, m_texture);
	m_Sprite2D->Set2DPosition(100, 150);
	m_Sprite2D->Init();


	//camera
	Vector3 CameraPos(0, 0, 20);
	Vector3 TargetPos(0, 0, 0);
	float fFovY = 0.7f;
	m_Camera = std::make_shared< Camera>();
	m_Camera->Init(CameraPos, TargetPos, fFovY, (GLfloat)screenWidth / screenHeight, 1.0f, 5000.0f, 1.0f);


	//plane
	m_model = std::make_shared< Models>("..\\Data\\Model\\Plan.nfg", NFG);

	m_Shaders = ResourceManagers::GetInstance()->GetShader("ColorShader");
	ResourceManagers::GetInstance()->AddShader("TextureShader");

	m_texture = std::make_shared< Texture>();
	m_texture->Init("..\\Data\\Textures\\Dirt.tga", GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);

	m_Plane = std::make_shared< Sprite3D>(m_model, m_Shaders, m_Camera, m_texture);
	m_Plane->Set3DScale(Vector3(25, 25, 25));
	m_Plane->Set3DPosition(Vector3(0, -10, 0));
	m_Plane->Init();

	//box
	m_model = std::make_shared < Models>("..\\Data\\Model\\box.nfg", NFG);
	m_Shaders = std::make_shared< Shaders>();
	m_Shaders->Init("..\\Data\\Shaders\\ColorShader.vs", "..\\Data\\Shaders\\TextureShader.fs");
	m_texture = std::make_shared< Texture>();
	m_texture->Init("..\\Data\\Textures\\plane_texture.tga", GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);

	m_Sprite3D = std::make_shared< Sprite3D>(m_model, m_Shaders, m_Camera, m_texture);
	m_Sprite3D->Set3DScale(Vector3(1, 1, 1));
	m_Sprite3D->Init();


	//text
	m_Shaders = std::make_shared< Shaders>();
	m_Shaders->Init("..\\Data\\Shaders\\TextShader.vs", "..\\Data\\Shaders\\TextShader.fs");
	std::shared_ptr<Font> font = std::make_shared<Font>("..\\Data\\fonts\\arial.ttf");
	m_text = std::make_shared< Text>(m_Shaders, font, "Sample Text 1", TEXT_COLOR::RED, Vector2(100, 150), 1.0);

}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
		GameStateMachine::GetInstance()->PopState();
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	m_Plane->Update(deltaTime);
	m_Sprite3D->Update(deltaTime);
	m_Sprite2D->Update(deltaTime);
	//m_Sprite3D1->Update(deltaTime);
}

void GSPlay::Draw()
{

	//3D
	m_Plane->Draw();
	m_Sprite3D->Draw();
	//m_Sprite3D1->Draw();

	//2D
	m_Sprite2D->Draw();
	m_text->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}
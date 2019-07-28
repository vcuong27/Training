#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
	Shaders* m_Shaders;
	Texture* m_texture;
	Models* m_model;
	Camera* m_Camera;

	//button
	m_Shaders = new Shaders();
	m_Shaders->Init("..\\Data\\Shaders\\TextureShader.vs", "..\\Data\\Shaders\\TextureShader.fs");

	m_texture = new Texture();
	m_texture->Init("..\\Data\\Textures\\btPlay.tga", GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);

	m_model = new Models();
	m_model->Init("..\\Data\\Model\\Sprite2D.nfg", NFG);

	m_Sprite2D = new Sprite2D(m_model, m_Shaders, m_texture);
	m_Sprite2D->Set2DPosition(100, 50);
	m_Sprite2D->Init();


	//camera
	Vector3 CameraPos(5, 20, 20);
	Vector3 TargetPos(0, 0, 0);
	float fFovY = 0.7f;
	m_Camera = new Camera();
	m_Camera->Init(CameraPos, TargetPos, fFovY, (GLfloat)screenWidth / screenHeight, 1.0f, 5000.0f, 1.0f);


	//plane
	m_model = new Models();
	m_model->Init("..\\Data\\Model\\Plan.nfg", NFG);
	m_Shaders = new Shaders();
	m_Shaders->Init("..\\Data\\Shaders\\ColorShader.vs", "..\\Data\\Shaders\\TextureShader.fs");
	m_texture = new Texture();
	m_texture->Init("..\\Data\\Textures\\Dirt.tga", GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);

	m_Plane = new Sprite3D(m_model, m_Shaders, m_Camera, m_texture);
	m_Plane->Set3DScale(Vector3(25, 25, 25));
	m_Plane->Set3DPosition(Vector3(0, -10, 0));
	m_Plane->Init();

	//box
	m_model = new Models();
	m_model->Init("..\\Data\\Model\\box.nfg", NFG);
	m_Shaders = new Shaders();
	m_Shaders->Init("..\\Data\\Shaders\\ColorShader.vs", "..\\Data\\Shaders\\TextureShader.fs");
	m_texture = new Texture();
	m_texture->Init("..\\Data\\Textures\\plane_texture.tga", GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);

	m_Sprite3D = new Sprite3D(m_model, m_Shaders, m_Camera, m_texture);
	m_Sprite3D->Set3DScale(Vector3(1, 1, 1));
	m_Sprite3D->Init();


	//cirle
	m_model = new Models();
	m_model->Init("..\\Data\\Model\\Bila.nfg", NFG);
	m_Shaders = new Shaders();
	m_Shaders->Init("..\\Data\\Shaders\\TextureShader.vs", "..\\Data\\Shaders\\TextureShader.fs");
	m_texture = new Texture();
	m_texture->Init("..\\Data\\Textures\\Rock.tga", GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);

	m_Sprite3D1 = new Sprite3D(m_model, m_Shaders, m_Camera, m_texture);
	m_Sprite3D1->Init();
	m_Sprite3D1->Set3DScale(Vector3(0.05, 0.05, 0.05));


	//text
	m_Shaders = new Shaders();
	m_Shaders->Init("..\\Data\\Shaders\\TextShader.vs", "..\\Data\\Shaders\\TextShader.fs");
	Font* font = Font::createWithFiles("..\\Data\\fonts\\arial.ttf");
	m_text = new Text(m_Shaders, font, "Sample Text", EColor::RED, Vector2(10, 50), 1.0);
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	//Init game play
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
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	m_Plane->Update(deltaTime);
	m_Sprite3D->Update(deltaTime);
	m_Sprite2D->Update(deltaTime);
	m_Sprite3D1->Update(deltaTime);
}

void GSPlay::Draw()
{

	//3D
	m_Plane->Draw();
	m_Sprite3D->Draw();
	m_Sprite3D1->Draw();

	//2D
	m_Sprite2D->Draw();
	m_text->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}
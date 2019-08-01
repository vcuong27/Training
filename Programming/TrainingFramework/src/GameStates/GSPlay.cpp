#include <sstream>
#include <iomanip>
#include <thread>

#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Text.h"
#include "Player.h"
#include "Enermy.h"
#include "Bullet.h"

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
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("Player");
	m_Player = std::make_shared<Player >(model, shader, texture);
	m_Player->Set2DPosition(screenWidth / 2, screenHeight - 100);
	m_Player->SetSize(50, 50);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
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
	if (key == KEY_LEFT)
	{
		m_Player->MoveLeft();
	}
	else if (key == KEY_RIGHT)
	{
		m_Player->MoveRight();
	}

	LOGI("HandleKeyEvents =  %d\n", key);
}

void GSPlay::HandleMouseEvents(int x, int y)
{
}


void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	CreateRandomEnermy();
}

void GSPlay::Update(float deltaTime)
{

	//update player
	m_Player->Update(deltaTime);

	if (m_Player->CanShoot())
		m_Player->Shoot(m_listBullet);


	//update enermies
	for (auto enermy : m_listEnermy)
	{
		if (enermy->IsActive())
			enermy->Update(deltaTime);
	}

	//update bullets
	for (auto bullet : m_listBullet)
	{
		if (bullet->IsActive())
			bullet->Update(deltaTime);
	}

	//update Score
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << 1.0f / deltaTime;
	std::string fps ="FPS: " + stream.str();
	m_score->setText(fps);
}

void GSPlay::Draw()
{
	//ground
	m_BackGround->Draw();

	for (auto enermy : m_listEnermy)
		if (enermy->IsActive())
			enermy->Draw();

	m_Player->Draw();

	for (auto bullet : m_listBullet)
		if (bullet->IsActive())
			bullet->Draw();

	//UI
	m_score->Draw();
}

void GSPlay::CreateRandomEnermy()
{

	int range = screenWidth - 10 + 1;
	int num = rand() % range + 10;

	Vector2 pos;
	pos.x = num;
	pos.y = 10;

	for (auto enermy : m_listEnermy)
	{
		if (!enermy->IsActive())
		{
			enermy->SetActive(true);
			enermy->Set2DPosition(pos);
			return;
		}

	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Enermy_1");

	std::shared_ptr<Enermy> enermy = std::make_shared<Enermy>(model, shader, texture);
	enermy->Set2DPosition(pos);
	enermy->SetSize(40, 40);
	enermy->SetRotation(180);
	m_listEnermy.push_back(enermy);
}

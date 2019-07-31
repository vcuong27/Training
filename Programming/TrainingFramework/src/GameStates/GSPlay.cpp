#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Text.h"
#include "Player.h"
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
}


void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	
}

void GSPlay::Update(float deltaTime)
{
	//player
	m_Player->Update(deltaTime);

	if (m_Player->CanShoot())
		m_Player->Shoot(m_listBullet);

	//update bullets
	for (auto bullet : m_listBullet)
	{
		if (bullet->IsActive())
		{
			bullet->Update(deltaTime);
			Vector2 pos = bullet->Get2DPosition();
			if (pos.y <= 20)
				bullet->SetActive(false);
		}
	}

}

void GSPlay::Draw()
{
	//ground
	m_BackGround->Draw();



	m_Player->Draw();
	
	
	for (auto bullet : m_listBullet)
	{
		if (bullet->IsActive())
			bullet->Draw();
	}



	//UI
	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}

std::shared_ptr<Bullet> GSPlay::GetBullet()
{
	for (auto bullet : m_listBullet)
	{
		if (!bullet->IsActive())
			return bullet;
	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
	bullet->SetSize(20, 20);

	m_listBullet.push_back(bullet);
	return bullet;
}

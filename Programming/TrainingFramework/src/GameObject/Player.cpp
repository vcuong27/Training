#include "Player.h"
#include "GameManager/ResourceManagers.h"

Player::Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_move = MOVE::NONE;
	m_MaxCooldown = 0.05;
	m_Cooldown = 0.0;
	m_speed = 500;
}

Player::~Player()
{
}

void Player::MoveLeft()
{
	m_move = MOVE::LEFT;
}

void Player::MoveRight()
{
	m_move = MOVE::RIGHT;
}

void Player::Update(GLfloat deltatime)
{
	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltatime;
	}

	if (m_move == MOVE::LEFT)
	{
		Vector2 pos = Get2DPosition();
		pos.x = pos.x - m_speed * deltatime;
		Set2DPosition(pos);
		m_move = MOVE::NONE;
	}

	if (m_move == MOVE::RIGHT)
	{
		Vector2 pos = Get2DPosition();
		pos.x = pos.x + m_speed * deltatime;
		Set2DPosition(pos);
		m_move = MOVE::NONE;
	}
}

bool Player::CanShoot()
{
	return (m_Cooldown <= 0);
}

void Player::Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet)
{
	m_Cooldown = m_MaxCooldown;
	for (auto bullet : listBullet)
	{
		if (!bullet->IsActive())
		{
			bullet->SetActive(true);
			bullet->Set2DPosition(Get2DPosition());
			return;
		}

	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
	bullet->SetSize(20, 20);
	bullet->Set2DPosition(Get2DPosition());

	listBullet.push_back(bullet);
}

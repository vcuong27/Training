#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_speed = 500.0;
	m_active = true;
}

Bullet::~Bullet()
{
}

void Bullet::Update(GLfloat deltatime)
{
	if (!m_active)
		return;
	Vector2 pos = Get2DPosition();
	pos.y = pos.y - m_speed * deltatime;
	Set2DPosition(pos);
}

bool Bullet::IsActive()
{
	return m_active;
}

void Bullet::SetActive(bool status)
{
	m_active = status;
}

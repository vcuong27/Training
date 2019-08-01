#include "Enermy.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

Enermy::Enermy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_active = false;
	m_speed = 250;
}

Enermy::~Enermy()
{
}


void Enermy::Update(float deltaTime)
{
	if (!m_active)
		return;
	Vector2 pos = Get2DPosition();
	pos.y = pos.y + m_speed * deltaTime;
	Set2DPosition(pos);

	if (pos.y > screenHeight)
		m_active = false;
}


bool Enermy::IsActive()
{
	return m_active;
}

void Enermy::SetActive(bool status)
{
	m_active = status;
}

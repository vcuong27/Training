#pragma once

#include "Sprite2D.h"

class Enermy : public Sprite2D
{
public:
	Enermy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Enermy();
	bool		IsActive();
	void		SetActive(bool status);

	void Update(float deltaTime) override;

private:
	float	m_speed;
	bool	m_active;
};

#pragma once
#include "Sprite2D.h"

class Bullet  : public Sprite2D
{
public:
	Bullet(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Bullet();

	void		Update(GLfloat deltatime) override;
	bool		IsActive();
	void		SetActive(bool status);
private:
	float	m_speed;
	bool	m_active;
};

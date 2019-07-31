#pragma once
#include "Sprite2D.h"
#include "Bullet.h"

class Player : public Sprite2D
{
	enum class MOVE
	{
		NONE,
		LEFT,
		RIGHT
	};

public:
	Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Player();

	void MoveLeft();
	void MoveRight();

	void Update(GLfloat deltatime) override;

	bool CanShoot();
	void Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet);


private:
	MOVE m_move;
	float m_speed;
	float m_MaxCooldown;
	float m_Cooldown;
};

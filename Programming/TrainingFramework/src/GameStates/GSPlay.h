#pragma once
#include "gamestatebase.h"

class Player;
class Bullet;
class Enermy;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init()override;
	void Exit()override;

	void Pause()override;
	void Resume()override;

	void HandleEvents() override;
	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleMouseEvents(int x, int y) override;

	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void Update(float deltaTime) override;
	void Draw() override;
	

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Bullet>> m_listBullet;
	std::vector<std::shared_ptr<Enermy>> m_listEnermy;

	void CreateRandomEnermy();
};


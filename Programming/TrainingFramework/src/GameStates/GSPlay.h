#pragma once
#include "gamestatebase.h"

class Player;
class Bullet;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	
	void SetNewPostionForBullet();



private:


	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Bullet>> m_listBullet;
	std::vector<std::shared_ptr<Bullet>> m_listEnermy;

	std::shared_ptr<Bullet> GetBullet();
	
};


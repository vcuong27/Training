#pragma once
#include "gamestatebase.h"

class Sprite2D;
class Sprite3D;
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


	Sprite2D* m_Sprite2D;
	Sprite3D* m_Plane;
	Sprite3D* m_Sprite3D1;
	Sprite3D* m_Sprite3D;
	Text* m_text;
};


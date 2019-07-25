#include "GSPlay.h"
#include "game\GamePlay.h"
#include "CollisionManagers.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

#define SManager SceneManager::GetInstance()

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
	
}


void GSPlay::Init()
{
	//Init game play
	GamePlay::GetInstance();
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
	GamePlay::GetInstance()->HandleKeyEvents( key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	GamePlay::GetInstance()->HandleTouchEvents( x,  y,  bIsPressed);
}

void GSPlay::Update( float deltaTime)
{
	//update menu UI 
	CollisionManagers::GetInstance()->update(deltaTime);
	GamePlay::GetInstance()->update(deltaTime);
}

void GSPlay::Draw()
{
	GamePlay::GetInstance()->draw();
}

void GSPlay::SetNewPostionForBullet()
{
	GamePlay::GetInstance()->SetNewPostionForBullet();
}
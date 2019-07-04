#include "stdafx.h"
#include "GSIntro.h"
#include "Shaders.h"
#include "Vertex.h"
#include "GSMenu.h"

GSIntro::GSIntro()
{
	//Init();
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	//triangle data (heap)
	
}

void GSIntro::Exit()
{
	
}


void GSIntro::Pause()
{
	
}

void GSIntro::Resume()
{
	
}


void GSIntro::HandleEvents(GameStateMachine* game)
{
	
}

void GSIntro::HandleKeyEvents(GameStateMachine* game, GLint key, bool bIsPressed)
{
	if(key == KEY_BACK) 
	{
		game->Quit();
	}
	else
	game->ChangeState(STATE_Menu);
}

void GSIntro::HandleTouchEvents(GameStateMachine* game, GLint x, GLint y, bool bIsPressed)
{

}

void GSIntro::Update(GameStateMachine* game, GLfloat deltaTime)
{
	
}

void GSIntro::Draw(GameStateMachine* game)
{

}

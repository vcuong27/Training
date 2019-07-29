#include "GSIntro.h"

GSIntro::GSIntro()
{
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
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


void GSIntro::HandleEvents()
{
	
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Play);

}

void GSIntro::HandleTouchEvents(int x, int y, bool bIsPressed)
{

}

void GSIntro::Update(float deltaTime)
{
	
}

void GSIntro::Draw()
{

}

#include "Application.h"

#include "GameStateMachine.h"

Application::Application(void)
{
}


Application::~Application(void)
{
}


void Application::Init()
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
	GameStateMachine::GetInstance()->ChangeState(STATE_Menu);
}

void Application::Update(GLfloat deltaTime)
{
	if(GameStateMachine::GetInstance()->NeedsToChangeState())
	{
		GameStateMachine::GetInstance()->PerformStateChange();
	}
	GameStateMachine::GetInstance()->Update(deltaTime);
	
	if (GameStateMachine::GetInstance()->isRunning() == false)
		Exit();
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GameStateMachine::GetInstance()->Draw();
}

void Application::HandleKeyEvent( unsigned char key, bool bIsPresseded)
{
	if(bIsPresseded)
		GameStateMachine::GetInstance()->HandleKeyEvents(key,bIsPresseded);
	
}

void Application::HandleTouchEvent(GLint x, GLint y, bool bIsPresseded)
{
	GameStateMachine::GetInstance()->HandleTouchEvents(x,y,bIsPresseded);
}

void Application::Exit()
{
	GameStateMachine::GetInstance()->Cleanup();
	GameStateMachine::FreeInstance();
	exit(0);
}

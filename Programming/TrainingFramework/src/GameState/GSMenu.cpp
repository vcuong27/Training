#include "GSMenu.h"
#include "Button.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Wave.h"
extern GLint screenWidth;
extern GLint screenHeight;

#define SManager SceneManager::GetInstance()
#define RsManager ResourceManager::GetInstance()

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}

void  btPlayClick(GameStateMachine* game)
{
	Wave one("D:/Training/trunk/Programming/Data/Sounds/click.wav");
	one.play(0);
	game->ChangeState(STATE_Play);
}

void  btExitClick(GameStateMachine* game)
{
	game->Quit();
}

void GSMenu::Init()
{

#ifdef ANDROID
	RsManager->Init("/sdcard/Data/RM_android.txt");
#else
	RsManager->Init("../Data/RM.txt");
#endif
	m_listButton.clear();

	Button*		bt;
	Models*		m_temp_mod		= RsManager->GetModels(1);
	Shaders*	m_temp_shad		= RsManager->GetShaders(1);
	Texture*	m_pTexture		= RsManager->GetTexture(0);
	
	GLint dHeight		= screenHeight/8; 
	GLint iCenterWidth	= screenWidth/2 - screenWidth/8;

	bt= new Button();
	bt->SetShaders(m_temp_shad);
	bt->SetModels(m_temp_mod);
	bt->SetTexture(m_pTexture);
	bt->Set2DPosition(iCenterWidth, 1 * dHeight);
	bt->Init();
	bt->SetOnClick(btPlayClick);
	SManager->addObject(bt);
	m_listButton.push_back(bt);

	m_pTexture		= RsManager->GetTexture(1);
	bt= new Button();
	bt->SetShaders(m_temp_shad);
	bt->SetModels(m_temp_mod);
	bt->SetTexture(m_pTexture);
	bt->Set2DPosition(iCenterWidth, 2 * dHeight);
	bt->Init();
	bt->SetOnClick(btExitClick);
	SManager->addObject(bt);
	m_listButton.push_back(bt);


	m_pTexture		= RsManager->GetTexture(5);
	bt= new Button();
	bt->SetShaders(m_temp_shad);
	bt->SetModels(m_temp_mod);
	bt->SetTexture(m_pTexture);
	bt->Set2DPosition(iCenterWidth, 3 * dHeight);
	bt->Init();
	bt->SetOnClick(btExitClick);
	SManager->addObject(bt);
	m_listButton.push_back(bt);

}

void GSMenu::Exit()
{
	SManager->FreeInstance();
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents(GameStateMachine* game)
{

}

void GSMenu::HandleKeyEvents(GameStateMachine* game, GLint key, bool bIsPressed)
{
	if (key == KEY_BACK)
		game->Quit();
}

void GSMenu::HandleTouchEvents(GameStateMachine* game, GLint x, GLint y, bool bIsPressed)
{
	for (std::list<Button*>::iterator it = m_listButton.begin(); it != m_listButton.end(); it++)
	{
		(*it)->HandleTouchEvents(game, x, y,bIsPressed);
	}
}

void GSMenu::Update(GameStateMachine* game, GLfloat deltaTime)
{

}

void GSMenu::Draw(GameStateMachine* game)
{
	SManager->Draw();
}

#include "stdafx.h"
#include "GSMenu.h"
#include "Button.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "MKSocial.h"

extern GLint screenWidth;
extern GLint screenHeight;

#define SManager SceneManager::GetInstance()
#define RsManager ResourceManager::GetInstance()

GSMenu::GSMenu()
{
	//m_isLogin=false;

}


GSMenu::~GSMenu()
{
}

void  btPlayClick(GameStateMachine* game)
{
	game->ChangeState(STATE_Play);
}
void  btLoginGameAPIClick(GameStateMachine* game)
{
	MKSocial::GetInstance()->LoginSNS(GOOGLE);
}
void  btLogoutGameAPIClick(GameStateMachine* game)
{
	MKSocial::GetInstance()->LogoutSNS(GOOGLE);
}
void  btLoginFaceClick(GameStateMachine* game)
{
	MKSocial::GetInstance()->LoginSNS(FACEBOOK);
}
void  btLogoutFaceClick(GameStateMachine* game)
{
	MKSocial::GetInstance()->LogoutSNS(FACEBOOK);
}
void  btExitClick(GameStateMachine* game)
{
	game->Quit();
}

void GSMenu::Init()
{

#ifdef ANDROID
	RsManager->Init("/sdcard/Resources/RM_android.txt");
#else
	RsManager->Init("../Resources/RM.txt");
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
	bt->Set2DPosition(iCenterWidth, dHeight);
	bt->Init();
	bt->SetOnClick(btPlayClick);
	SManager->addObject(bt);
	m_listButton.push_back(bt);

	//m_pTexture		= RsManager->GetTexture(1);
	//bt= new Button();
	//bt->SetShaders(m_temp_shad);
	//bt->SetModels(m_temp_mod);
	//bt->SetTexture(m_pTexture);
	//bt->Set2DPosition(iCenterWidth, 2 * dHeight);
	//bt->Init();
	//bt->SetOnClick(btLoginGameAPIClick);
	//SManager->addObject(bt);
	//m_listButton.push_back(bt);

	//m_pTexture		= RsManager->GetTexture(2);
	//bt= new Button();
	//bt->SetShaders(m_temp_shad);
	//bt->SetModels(m_temp_mod);
	//bt->SetTexture(m_pTexture);
	//bt->Set2DPosition(iCenterWidth, 3 * dHeight);
	//bt->Init();
	//bt->SetOnClick(btLoginFaceClick);
	//SManager->addObject(bt);
	//m_listButton.push_back(bt);

	//m_pTexture		= RsManager->GetTexture(3);
	//bt= new Button();
	//bt->SetShaders(m_temp_shad);
	//bt->SetModels(m_temp_mod);
	//bt->SetTexture(m_pTexture);
	//bt->Set2DPosition(iCenterWidth, 4 * dHeight);
	//bt->Init();
	//bt->SetOnClick(btLogoutGameAPIClick);
	//SManager->addObject(bt);
	//m_listButton.push_back(bt);

	//m_pTexture		= RsManager->GetTexture(4);
	//bt= new Button();
	//bt->SetShaders(m_temp_shad);
	//bt->SetModels(m_temp_mod);
	//bt->SetTexture(m_pTexture);
	//bt->Set2DPosition(iCenterWidth, 5 * dHeight);
	//bt->Init();
	//bt->SetOnClick(btLogoutFaceClick);
	//SManager->addObject(bt);
	//m_listButton.push_back(bt);

	m_pTexture		= RsManager->GetTexture(5);
	bt= new Button();
	bt->SetShaders(m_temp_shad);
	bt->SetModels(m_temp_mod);
	bt->SetTexture(m_pTexture);
	bt->Set2DPosition(iCenterWidth, 6 * dHeight);
	bt->Init();
	bt->SetOnClick(btExitClick);
	SManager->addObject(bt);
	m_listButton.push_back(bt);

}

void GSMenu::Exit()
{
	SManager->FreeInstance();
	RsManager->FreeInstance();
	//delete m_pCam;
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
	
}

void GSMenu::HandleTouchEvents(GameStateMachine* game, GLint x, GLint y, bool bIsPressed)
{
	for (std::list<Button*>::iterator it = m_listButton.begin(); it != m_listButton.end(); it++)
	{
		(*it)->HandleTouchEvents(game, x, y,bIsPressed);
		//if((*it)->IsHandle()) break;
	}
}

void GSMenu::Update(GameStateMachine* game, GLfloat deltaTime)
{

}

void GSMenu::Draw(GameStateMachine* game)
{
	SManager->Draw();
}

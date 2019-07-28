/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"

#include "GameStatebase.h"

GameStateBase* GameStateBase::CreateState(StateTypes stt)
{
	GameStateBase * gs = 0;
	switch (stt)
	{
	case STATE_INVALID:
		break;
	case STATE_Intro:
		gs = new GSIntro();
		break;
	case STATE_Menu:
		gs = new GSMenu();
		break;
	case STATE_Play:
		gs = new GSPlay();
		break;
	default:
		break;
	}
	return gs;
}
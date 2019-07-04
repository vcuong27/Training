/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "GameStateBase.h"
#include "GsIntro.h"
#include "GsLoading.h"
#include "GsMenu.h"
#include "GsPlay.h"
#include "GsSetting.h"

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateTypes::STATE_INVALID:
		break;
	case StateTypes::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		break;
	case StateTypes::STATE_LOADING:
		gs = std::make_shared<GsLoading>();
		break;
	case StateTypes::STATE_MENU:
		gs = std::make_shared<GsMenu>();
		break;
	case StateTypes::STATE_SETTING:
		gs = std::make_shared<GsSetting>();
		break;
	case StateTypes::STATE_PLAY:
		gs = std::make_shared<GsPlay>();
		break;
	default:
		break;
	}
	return gs;
}
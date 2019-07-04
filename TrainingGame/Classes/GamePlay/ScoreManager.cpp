#include "ScoreManager.h"
#include "Managers\SoundMgr.h"
void ScoreManager::Init(Node *match3Scene)
{
#if SCORE_ENABLED

	auto layer_play = match3Scene->getChildByName("layer_play");
	ScoreText = (Label*)layer_play->getChildByName("score_text_label");
	GPSText = (Label*)layer_play->getChildByName("GPSText_label");
	ComboText = (Label*)layer_play->getChildByName("combo_label");
	ComboText->setColor(Color3B(YELLOW));


	SoundMgr::getInstance()->preloadEffect("Streak_01.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_02.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_03.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_04.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_05.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_06.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_07.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_08.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_09.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_10.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_11.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_12.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_13.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_14.mp3");
	SoundMgr::getInstance()->preloadEffect("Streak_15.wav");
	SoundMgr::getInstance()->preloadEffect("Streak_16.wav");
	SoundMgr::getInstance()->preloadEffect("Streak_18.wav");
	SoundMgr::getInstance()->preloadEffect("Streak_20.wav");
#endif
}

void ScoreManager::UpdateScoreText(int scoreValue)
{
	std::ostringstream oss;
	oss << "Damage: " << scoreValue;
	std::string scoreString = oss.str();

	ScoreText->setString(scoreString);

	oss.str("");
	oss.clear();
	oss << "DPS: " << (int)(scoreValue / m_elapsedTime);
	std::string GPSString = oss.str();
	GPSText->setString(GPSString);

}

void ScoreManager::AddScore(int value)
{
#if SCORE_ENABLED
	if (m_counterValue != m_currentScore)
	{
		m_scoreMulti++;

		checkCombo(m_scoreMulti);
	}
	if (m_currentScore == 0)
	{
		SoundMgr::getInstance()->playEffect("Streak_01.mp3", false, 1.0f, 1.0f, 1.0f);
	}
	m_currentScore += value * m_scoreMulti;
	m_lerpTime = 0.0f;
#endif
}

void ScoreManager::update(float delta)
{
	m_elapsedTime += delta;

	if (m_currentScore != m_counterValue)
	{
		m_lerpTime += delta;
		m_counterValue += (int)((m_currentScore - m_counterValue) * (m_lerpTime / LERPTIME));
		UpdateScoreText(m_counterValue);
	}

	if (((float)m_lerpTime / LERPTIME) > 0.9f)
	{
		m_counterValue = m_currentScore;
		m_lerpTime = 0.0F;
		m_scoreMulti = 1;
		UpdateScoreText(m_currentScore);
		ComboText->setString("");
	}
}

void ScoreManager::checkCombo(int combo)
{
	if (combo < 1)
		return;

	std::ostringstream oss;
	if (combo >= 10)
	{
		oss << " COMBO XXX" << m_scoreMulti;

	}
	else if (combo >= 7)
	{
		oss << " COMBo XX" << m_scoreMulti;

	}
	else if (combo >= 5)
	{
		oss << " COMbo XX" << m_scoreMulti;
	}
	else if (combo >= 3)
	{
		oss << " COmbo X" << m_scoreMulti;

	}
	else if (combo > 1)
	{
		oss << " Combo X" << m_scoreMulti;
	}

	std::string comboString = oss.str();
	ComboText->setString(comboString);
	/*ComboText->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - ComboText->getContentSize().height * 4));*/

	ComboText->stopAllActions();
	ComboText->setRotation(0);
	ComboText->setScale(1);

	RotateBy* rotateBy = RotateBy::create(0.25f, 20.0f);
	RotateBy* rotateBy2 = RotateBy::create(0.25f, -20.0f);

	ScaleTo* actionScaleOut = ScaleTo::create(0.25f, 1.4f, 1.4f);
	ScaleTo* actionScaleIn = ScaleTo::create(0.25f, 1, 1);

	Sequence* rot = Sequence::create(rotateBy, rotateBy->reverse(), rotateBy2, rotateBy2->reverse(), nullptr);
	Sequence* sca = Sequence::create(actionScaleOut, actionScaleIn, actionScaleOut->clone(), actionScaleIn->clone(), nullptr);

	Spawn* mySpawn = Spawn::createWithTwoActions(rot, sca);
	ComboText->runAction(mySpawn);

	switch (combo)
	{
	case 2:
		SoundMgr::getInstance()->playEffect("Streak_02.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 3:
		SoundMgr::getInstance()->playEffect("Streak_03.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 4:
		SoundMgr::getInstance()->playEffect("Streak_04.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 5:
		SoundMgr::getInstance()->playEffect("Streak_05.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 6:
		SoundMgr::getInstance()->playEffect("Streak_06.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 7:
		SoundMgr::getInstance()->playEffect("Streak_07.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 8:
		SoundMgr::getInstance()->playEffect("Streak_08.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 9:
		SoundMgr::getInstance()->playEffect("Streak_09.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 10:
		SoundMgr::getInstance()->playEffect("Streak_10.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 11:
		SoundMgr::getInstance()->playEffect("Streak_11.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 12:
		SoundMgr::getInstance()->playEffect("Streak_12.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 13:
		SoundMgr::getInstance()->playEffect("Streak_13.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 14:
		SoundMgr::getInstance()->playEffect("Streak_14.mp3", false, 1.0f, 1.0f, 1.0f);
		break;
	case 15:
		SoundMgr::getInstance()->playEffect("Streak_15.wav", false, 1.0f, 1.0f, 1.0f);
		break;
	case 16:
		SoundMgr::getInstance()->playEffect("Streak_16.wav", false, 1.0f, 1.0f, 1.0f);
		break;
	case 18:
		SoundMgr::getInstance()->playEffect("Streak_18.wav", false, 1.0f, 1.0f, 1.0f);
		break;
	case 20:
		SoundMgr::getInstance()->playEffect("Streak_20.wav", false, 1.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}
}

ScoreManager::~ScoreManager()
{

}

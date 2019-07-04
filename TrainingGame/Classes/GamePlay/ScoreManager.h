#pragma once

#include "game_config.h"
#include "base/Singleton.h"

class ScoreManager : public CSingleton<ScoreManager>
{
public:
	int m_currentScore = 0;
	int m_counterValue = 0;
	int m_scoreMulti = 1;
	//int m_scoreBonus = 0;
	float m_lerpTime = 0;
	float m_elapsedTime = 0;

	Size visibleSize;
	Vec2 origin;

	Label* ScoreText;
	Label* GPSText;
	//Label* StatusText;
	Label* ComboText;

	void Init(Node *match3Scene);
	void UpdateScoreText(int scoreValue);
	void AddScore(int value);
	void update(float delta);
	void checkCombo(int combo);

	~ScoreManager();
};
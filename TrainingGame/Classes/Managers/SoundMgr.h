/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#ifndef  _GAME_SOUND_MGR_H_
#define  _GAME_SOUND_MGR_H_

#include "game_config.h"


class SoundMgr : public CSingleton < SoundMgr >
{
public:
	SoundMgr();
	~SoundMgr();

	void initialize();
	void exit();
	void pause();
	void resume();
	void update(float deltaTime);

	void increaseBackgroundMusicVolume();
	void decreaseBackgroundMusicVolume();
	void preloadBackgroundMusic(const char* name);
	void unloadBackgroundMusic(const char* name);
	void playBackgroundMusic(const char* name, bool loop = false);
	void stopBackgroundMusic(bool releaseData = false);

	void increaseEffectsVolume();
	void decreaseEffectsVolume();
	void preloadEffect(const char* name);
	void unloadEffect(const char* name);
	unsigned int playEffect(const char* name, bool loop = false, float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);
	void pauseEffect(unsigned int soundId);

private:
	float m_backgroundSound;
	float m_effectSound;

};

#endif
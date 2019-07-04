/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "SoundMgr.h"


SoundMgr::SoundMgr()
{
	initialize();
}

SoundMgr::~SoundMgr()
{
#if USE_AUDIO_ENGINE
	AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::end();
#endif
}

void SoundMgr::initialize()
{
	SimpleAudioEngine::getInstance();
	m_backgroundSound = 5;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(m_backgroundSound);
	m_effectSound = 5;
	SimpleAudioEngine::getInstance()->setEffectsVolume(m_effectSound);
}

void SoundMgr::exit()
{
	//nothing to do
}

void SoundMgr::pause()
{

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif

}

void SoundMgr::resume()
{

#if USE_AUDIO_ENGINE
	AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif

}

void SoundMgr::update(float deltaTime)
{
	//let's coccos engine handle
}

void SoundMgr::increaseBackgroundMusicVolume()
{
#if USE_SIMPLE_AUDIO_ENGINE
	m_backgroundSound++;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(m_backgroundSound);
#endif
}

void SoundMgr::decreaseBackgroundMusicVolume()
{
#if USE_SIMPLE_AUDIO_ENGINE
	m_backgroundSound--;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(m_backgroundSound);
#endif
}

void SoundMgr::playBackgroundMusic(const char * name, bool loop)
{
#if USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->playBackgroundMusic(name, loop);
#endif
}

void SoundMgr::stopBackgroundMusic(bool releaseData)
{
#if USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(releaseData);
#endif
}

void SoundMgr::increaseEffectsVolume()
{
#if USE_SIMPLE_AUDIO_ENGINE
	m_effectSound++;
	SimpleAudioEngine::getInstance()->setEffectsVolume(m_effectSound);
#endif
}

void SoundMgr::decreaseEffectsVolume()
{
#if USE_SIMPLE_AUDIO_ENGINE
	m_effectSound--;
	SimpleAudioEngine::getInstance()->setEffectsVolume(m_effectSound);
#endif
}

unsigned int SoundMgr::playEffect(const char * name, bool loop, float pitch, float pan, float gain)
{
#if USE_SIMPLE_AUDIO_ENGINE
	return SimpleAudioEngine::getInstance()->playEffect(name, loop, pitch, pan, gain);
#endif
	return 0;
}

void SoundMgr::pauseEffect(unsigned int soundId)
{
#if USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->pauseEffect(soundId);
#endif
}

void SoundMgr::preloadBackgroundMusic(const char * name)
{
#if USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(name);
#endif
}

void SoundMgr::unloadBackgroundMusic(const char * name)
{
#if USE_SIMPLE_AUDIO_ENGINE
	//Coccos simple sound does not support
	//SimpleAudioEngine::getInstance()->unloadBackgroundMusic(name);
#endif
}

void SoundMgr::preloadEffect(const char * name)
{
#if USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->preloadEffect(name);
#endif
}

void SoundMgr::unloadEffect(const char * name)
{
#if USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->unloadEffect(name);
#endif
}

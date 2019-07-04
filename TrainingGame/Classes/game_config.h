/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#ifndef  _GAME_CONFIG_H_
#define  _GAME_CONFIG_H_

//**************************************
//		INCLUDE
//**************************************
#include "base\Singleton.h"
#include "cocos2d.h"
#include "..\external\json\document.h"


//**************************************
//		DEFINE INGAME VALUE
//**************************************

#define GAME_DEFAUL_FONT				"fonts/Marker Felt.ttf"
#define GAME_DEFAUL_FONT_SIZE			24
#define GAME_DEFAUL_IMAGE				"default_image.png"


#define WIDTH 8
#define HEIGHT 10
#define NUMBER_OF_COLOR 4
#define SCALE 0.1f,0.1f
#define START_HEIGHT 450
#define START_MOVETIME 0.75f
#define SWAPTIME 0.45f
#define LERPTIME 3.0f
#define TIME_MODIFIER(j) (j - 1) * 0.125f + 0.2f

#define YELLOW 248, 212, 27
#define BLUE 107, 137, 210
#define MAGNETA 181, 55, 137
#define INDIGO 44, 22, 71
#define GREEN 15, 89, 89
#define TEAL 23, 166, 151
#define RED 217, 50, 64
#define CYAN 143, 212, 217
#define WILD 255, 255, 255
#define NONE 0, 0, 0

#define R_DOT "dot.png"
#define R_TILE "simpleBorder.png"

#define R_COLBOMB "columnIcon.png"
#define R_ROWBOMB "rowIcon.png"
#define R_ADJBOMB "adjacentIcon.png"
#define R_MATCHBOMB "colorBombIcon.png"

#define SCORE_NORMAL 10
#define SCORE_OVER_BONUS 20
#define SCORE_BOMB_BONUS 30


//**************************************
//		DEFINE INGAME FLAG
//**************************************

#define DEBUG_GAME = 1

#ifdef DEBUG_GAME
#define GAME_ASSERT CCASSERT
#define GAME_LOG CCLOG
#else
#define GAME_ASSERT 
#define GAME_LOG
#endif // DEBUG_GAME


//Enable debug information
#define DEBUG 0 
//Enable score system
#define SCORE_ENABLED 1
//Enable movement
#define MOVE_ENABLED 1
//Enable Bomb
#define BOMB_ENABLED 0
//Enable Collapse Column
#define COLLAPSE_ENABLED 1

// define for sound engine 
#define USE_SIMPLE_AUDIO_ENGINE 1
#define USE_AUDIO_ENGINE 0

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif


//**************************************
//		USING NAMESPACE
//**************************************

USING_NS_CC;







#endif // _GAME_CONFIG_H_


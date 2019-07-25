#pragma once
#include "Keycodes.h"

enum EEVENT_TYPE
{
	EET_GUI_EVENT = 0,
	EET_MOUSE_INPUT_EVENT,
	EET_KEY_INPUT_EVENT
};

//! Enumeration for all mouse input events
enum EMOUSE_INPUT_EVENT
{
	//! Left mouse button was pressed down.
	EMIE_LMOUSE_PRESSED_DOWN = 0,

	//! Right mouse button was pressed down.
	EMIE_RMOUSE_PRESSED_DOWN,

	//! Middle mouse button was pressed down.
	EMIE_MMOUSE_PRESSED_DOWN,

	//! Left mouse button was left up.
	EMIE_LMOUSE_LEFT_UP,

	//! Right mouse button was left up.
	EMIE_RMOUSE_LEFT_UP,

	//! Middle mouse button was left up.
	EMIE_MMOUSE_LEFT_UP,

	//! The mouse cursor changed its position.
	EMIE_MOUSE_MOVED,

	//! No real event. Just for convenience to get number of events
	EMIE_COUNT
};

//! Masks for mouse button states
enum E_MOUSE_BUTTON_STATE_MASK
{
	EMBSM_LEFT    = 0x01,
	EMBSM_RIGHT   = 0x02,
	EMBSM_MIDDLE  = 0x04,

	//! currently only on windows
	EMBSM_EXTRA1  = 0x08,

	//! currently only on windows
	EMBSM_EXTRA2  = 0x10,

	EMBSM_FORCE_32_BIT = 0x7fffffff
};
struct SEvent
{
	struct SMouseInput
	{
		//! X position of mouse cursor
		int X;

		//! Y position of mouse cursor
		int Y;

		//! A bitmap of button states. You can use isButtonPressed() to determine
		//! if a button is pressed or not.
		//! Currently only valid if the event was EMIE_MOUSE_MOVED
		int ButtonStates;

		//! Is the left button pressed down?
		bool isLeftPressed() const { return 0 != ( ButtonStates & EMBSM_LEFT ); }

		//! Is the right button pressed down?
		bool isRightPressed() const { return 0 != ( ButtonStates & EMBSM_RIGHT ); }

		//! Is the middle button pressed down?
		bool isMiddlePressed() const { return 0 != ( ButtonStates & EMBSM_MIDDLE ); }

		//! Type of mouse event
		EMOUSE_INPUT_EVENT Event;
	};

	//! Any kind of keyboard event.
	struct SKeyInput
	{
		//! Character corresponding to the key (0, if not a character)
		wchar_t Char;

		//! Key which has been pressed or released
		EKEY_CODE Key;
	};
};

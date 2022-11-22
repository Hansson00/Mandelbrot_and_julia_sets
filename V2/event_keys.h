#pragma once
#include "SDL.h"

/* Keystates. */
enum class KeyState
{
	DOWN, 
	UP
};

/* Possible input keys. */
enum class Key
{
	ESC,
	W, A, S, D,
	ONE, TWO, THREE,
	LSHIFT, LCTRL,
	PGUP, PGDN,
	LMOUSE
};

/* Struct containing inputs. */
struct KeyEvent
{
	KeyState key_state;
	Key key;
	uint32_t mouse_x;
	uint32_t mouse_y;
};
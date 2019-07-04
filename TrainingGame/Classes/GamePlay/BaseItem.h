#pragma once

#include "game_config.h"


enum TileType
{
	Normal,
	Obstacle,
	Breakable
};


enum MatchType
{
	None,
	Yellow,
	Blue,
	Teal,
	Red,
	Cyan,
	Green,
	Magneta,
	Indigo,
	Wild
};

enum BombType
{
	NotBomb,
	Column,
	Row,
	Adjacent,
	Color
};

class BaseItem
{
public:
	int xIndex;
	int yIndex;

	Vec2 worldPosition(int x, int y);
	void SetCoord(int x, int y);

	Sprite* sprite = nullptr;

	BaseItem();
	~BaseItem();
};
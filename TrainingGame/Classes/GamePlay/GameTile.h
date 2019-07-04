#pragma once

#include "BaseItem.h"

class GameTile : public BaseItem
{
public:

	TileType tileType = Normal;

	void Init(Node* match3Scene, int x, int y);

	GameTile();
	~GameTile();
};


#include "GameTile.h"



GameTile::GameTile()
{
}


GameTile::~GameTile()
{
}

void GameTile::Init(Node* match3Scene, int x, int y)
{
	SetCoord(x, y);

	sprite = Sprite::create(R_TILE);
	sprite->setPosition(worldPosition(x, y));
	sprite->setColor(Color3B(WILD));
	sprite->setOpacity(50);
	sprite->setScale(0.09);

	// add the sprite as a child to this layer
	match3Scene->addChild(sprite, 0);
}

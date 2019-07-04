#pragma once

#include "BaseItem.h"

class GamePiece : public BaseItem
{
public:

	bool m_isMoving = false;

	MatchType matchType;
	BombType bombType = NotBomb;
	Sprite* bombSprite = nullptr;

	void Init(int x, int y, MatchType mValue = None, int yOffset = 0, float movetime = 0.1f);
	void Move(int destX, int destY, float time);
	void ChangeColor(GamePiece match);
	void ChangeColor(MatchType value);
	Color3B Value2Vector(MatchType value);
	void Hightlight(bool on = true);
	void Clear();
	void ClearBomb();
	void onMouseDown(Event *event);
	void onMouseUp(Event *event);
	bool isEmpty();
	void SwitchBomb(BombType type);
	//bool onMouseMove(Event *event);

	bool operator==(const GamePiece &other) const
	{
		if (xIndex == other.xIndex
			&& yIndex == other.yIndex)
		{
			return true;
		}
		return false;
	}

	bool operator!=(const GamePiece &other) const
	{
		if (xIndex != other.xIndex
			|| yIndex != other.yIndex)
		{
			return true;
		}
		return false;
	}

	bool operator>(const GamePiece &other) const
	{
		if (xIndex > other.xIndex && yIndex > other.yIndex
			|| (xIndex > other.xIndex && yIndex == other.yIndex)
			|| (xIndex == other.xIndex && yIndex > other.yIndex))
		{
			return true;
		}
		return false;
	}

	bool operator<(const GamePiece &other) const
	{
		if (xIndex < other.xIndex && yIndex < other.yIndex
			|| (xIndex < other.xIndex && yIndex == other.yIndex)
			|| (xIndex == other.xIndex && yIndex < other.yIndex))
		{
			return true;
		}
		return false;
	}

	GamePiece();
	~GamePiece();
};


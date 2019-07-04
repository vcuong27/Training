#include "GamePiece.h"
#include "BoardManager.h"


GamePiece::GamePiece()
{
	//sprite = Sprite::create(R_DOT);
}

GamePiece::~GamePiece()
{
}

void GamePiece::Init(int x, int y, MatchType mValue, int yOffset, float moveTime)
{
	SetCoord(x, y);
	Clear();
	sprite = Sprite::create(R_DOT);
	sprite->getTexture()->generateMipmap();
	// sprite->getTexture()->setAntiAliasTexParameters();
	sprite->getTexture()->setTexParameters(Texture2D::TexParams{ GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE });
	sprite->setPosition(worldPosition(xIndex, yIndex) + Vec2(0, yOffset));
	ChangeColor(mValue);
	sprite->setScale(SCALE);

	// add the sprite as a child to this layer
	BoardManager::getInstance()->m_match3Scene->addChild(sprite, 0);

	EventListenerMouse* mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GamePiece::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(GamePiece::onMouseUp, this);
	//mouseListener->onMouseMove = CC_CALLBACK_1(GamePiece::onMouseMove, this);
	BoardManager::getInstance()->m_match3Scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, sprite);

	if (yOffset > 0)
	{
		Move(xIndex, yIndex, moveTime);
	}
}

Color3B GamePiece::Value2Vector(MatchType value)
{
	switch (value)
	{
	case Yellow:
		return Color3B(YELLOW);
		break;
	case Blue:
		return Color3B(BLUE);
		break;
	case Magneta:
		return Color3B(MAGNETA);
		break;
	case Indigo:
		return Color3B(INDIGO);
		break;
	case Green:
		return Color3B(GREEN);
		break;
	case Teal:
		return Color3B(TEAL);
		break;
	case Red:
		return Color3B(RED);
		break;
	case Cyan:
		return Color3B(CYAN);
		break;
	case Wild:
		return Color3B(WILD);
		break;
	default:
		return Color3B(NONE);
		break;
	}

	return Color3B(NONE);
}

void GamePiece::Hightlight(bool on)
{
	if (!m_isMoving 
		&& on
		&& sprite!=nullptr)
	{
		ScaleTo* actionScaleOut = ScaleTo::create(1.0f, 0.125f, 0.125f);
		ScaleTo* actionScaleIn = ScaleTo::create(1.0f, SCALE);
		EaseBackInOut *easeActionOut = EaseBackInOut::create(actionScaleOut);
		EaseBackInOut *easeActionIn = EaseBackInOut::create(actionScaleIn);
		sprite->runAction(Sequence::create(easeActionOut, easeActionIn, easeActionOut->clone(), easeActionIn->clone(), nullptr));
		if (bombType != NotBomb
			&& bombSprite != nullptr)
		{
			bombSprite->runAction(Sequence::create(easeActionOut->clone(), easeActionIn->clone(), easeActionOut->clone(), easeActionIn->clone(), nullptr));
		}
		return;
	}
	else if (!m_isMoving 
		&& !on
		&& sprite != nullptr)
	{
		sprite->stopAllActions();
		sprite->setScale(SCALE);
		if (bombType != NotBomb
			&& bombSprite != nullptr)
		{
			bombSprite->stopAllActions();
			bombSprite->setScale(SCALE);
		}
	}

}

void GamePiece::Clear()
{
	if (sprite != nullptr &&
		sprite->getParent())
	{
		sprite->stopAllActions();
		m_isMoving = false;
		matchType = None;
		if (bombType == Color)
		{
			bombType = NotBomb;
		}
		sprite->removeFromParentAndCleanup(true);
		sprite = nullptr;
	}
}

void GamePiece::ClearBomb()
{
	if (bombSprite != nullptr &&
		bombSprite->getParent())
	{
		bombType = NotBomb;
		bombSprite->stopAllActions();
		bombSprite->removeFromParentAndCleanup(true);
		bombSprite = nullptr;
	}
}

void GamePiece::onMouseDown(Event * event)
{
	EventMouse* e = (EventMouse*)event;
	Vec2 location;
	Size visibleSize = Director::getInstance()->getWinSize();
	location.y = visibleSize.height - e->getLocation().y;
	location.x = e->getLocation().x;

	auto target = event->getCurrentTarget();
	//Get the position of the current point relative to the button
	Point locationInNode = target->convertToNodeSpace(location);
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	//Check the click area
	if (rect.containsPoint(locationInNode))
	{
		//log("sprite began... x = %d, y = %d", xIndex, yIndex);
		BoardManager::getInstance()->ClickTile(this);
	}
	return;
}

void GamePiece::onMouseUp(Event * event)
{
	EventMouse* e = (EventMouse*)event;
	Vec2 location;
	Size visibleSize = Director::getInstance()->getWinSize();
	location.y = visibleSize.height - e->getLocation().y;
	location.x = e->getLocation().x;

	auto target = event->getCurrentTarget();
	//Get the position of the current point relative to the button
	Point locationInNode = target->convertToNodeSpace(location);
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	//Check the click area
	if (rect.containsPoint(locationInNode))
	{
		//log("sprite ended... x = %d, y = %d", xIndex, yIndex);
		BoardManager::getInstance()->ReleaseTile(this);
	}
	return;
}

bool GamePiece::isEmpty()
{
	if (this == nullptr
		|| sprite == nullptr)
	{
		return true;
	}
	return false;
}

void GamePiece::SwitchBomb(BombType type)
{
	bombType = type;
	switch (type)
	{
	case NotBomb:
	{
		ClearBomb();
		break;
	}
	case Column:
	{
		ClearBomb();
		bombSprite = Sprite::create(R_COLBOMB);
		bombSprite->setPosition(worldPosition(xIndex, yIndex));
		bombSprite->getTexture()->generateMipmap();
		bombSprite->getTexture()->setTexParameters(Texture2D::TexParams{ GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE });
		bombSprite->setScale(SCALE);

		// add the sprite as a child to this layer
		BoardManager::getInstance()->m_match3Scene->addChild(bombSprite, 1);
		break;
	}
	case Row:
	{
		ClearBomb();
		bombSprite = Sprite::create(R_ROWBOMB);
		bombSprite->setPosition(worldPosition(xIndex, yIndex));
		bombSprite->getTexture()->generateMipmap();
		bombSprite->getTexture()->setTexParameters(Texture2D::TexParams{ GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE });
		bombSprite->setScale(SCALE);

		// add the sprite as a child to this layer
		BoardManager::getInstance()->m_match3Scene->addChild(bombSprite, 1);
		break;
	}
	case Adjacent:
	{
		ClearBomb();
		bombSprite = Sprite::create(R_ADJBOMB);
		bombSprite->setPosition(worldPosition(xIndex, yIndex));
		bombSprite->getTexture()->generateMipmap();
		bombSprite->getTexture()->setTexParameters(Texture2D::TexParams{ GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE });
		bombSprite->setScale(SCALE);

		// add the sprite as a child to this layer
		BoardManager::getInstance()->m_match3Scene->addChild(bombSprite, 1);
		break;
	}
	case Color:
	{
		sprite->setTexture(R_MATCHBOMB);
		sprite->getTexture()->generateMipmap();
		sprite->getTexture()->setTexParameters(Texture2D::TexParams{ GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE });
		ChangeColor(Wild);
		break;
	}
	default:
		assert("Make bomb should never reach here");
		break;
	}
}

void GamePiece::Move(int destX, int destY, float time)
{
	if (!m_isMoving)
	{
		m_isMoving = true;
#if MOVE_ENABLED
		MoveTo* actionMove = MoveTo::create(time, worldPosition(destX, destY));
		EaseInOut *easeAction = EaseInOut::create(actionMove, 5.0f);

		CallFunc* setCo = CallFunc::create([&, destX, destY]() {
			SetCoord(destX, destY);
			sprite->setPosition(worldPosition(xIndex, yIndex));
			m_isMoving = false;
		});
		if (this != nullptr
			&& sprite != nullptr)
		{
			sprite->stopAllActions();
			sprite->setScale(SCALE);
			sprite->runAction(Sequence::create(easeAction, setCo, nullptr));
			if (bombSprite != nullptr)
			{
				MoveTo* actionMoveBomb = MoveTo::create(time, worldPosition(destX, destY));
				EaseInOut *easeActionBomb = EaseInOut::create(actionMoveBomb, 5.0f);
				bombSprite->runAction(easeActionBomb);
			}
		}
#else
		SetCoord(destX, destY);
		sprite->setPosition(worldPosition(xIndex, yIndex));
		m_isMoving = false;
#endif
	}
}

void GamePiece::ChangeColor(GamePiece match)
{
	//need to change renderer color as well
	matchType = match.matchType;
	sprite->setColor(Value2Vector(matchType));
}

void GamePiece::ChangeColor(MatchType value)
{
	matchType = value;
	sprite->setColor(Value2Vector(matchType));
}
#include "BaseItem.h"
#include "BoardManager.h"

Vec2 BaseItem::worldPosition(int x, int y)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	return Vec2(visibleSize.width / 6 + origin.x + 45 * x, visibleSize.height / 6 + origin.y + 45 * y);
}

void  BaseItem::SetCoord(int x, int y)
{
	xIndex = x;
	yIndex = y;

#if DEBUG
	std::ostringstream oss;
	oss << xIndex << "|" << yIndex;
	std::string coord = oss.str();

	auto label = Label::createWithTTF(coord, "fonts/good times rg.ttf", 12);
	label->setPosition(Vec2(worldPosition(xIndex, yIndex)));
	BoardManager::Instance().m_match3Scene->addChild(label, 1);
#endif
}

BaseItem::BaseItem()
{
}

BaseItem::~BaseItem()
{
	sprite = nullptr;
}

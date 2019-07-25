#pragma once

#include "Math.h"

class Config
{
public:
	static Config* getInstance();
	static void destroyInstance();

	void setScreenSize(const Vector2& size);
	const Vector2& getScreenSize() const;

private:
	static Config* _instance;
	Vector2 _screenSize;
};
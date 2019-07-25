#include "Config.h"

Config* Config::_instance = nullptr;

Config* Config::getInstance()
{
	if (!_instance)
	{
		_instance = new Config();
	}

	return _instance;
}

void Config::destroyInstance()
{
	delete _instance;
	_instance = nullptr;
}

void Config::setScreenSize(const Vector2& size)
{
	_screenSize = size;
}

const Vector2& Config::getScreenSize() const
{
	return _screenSize;
}

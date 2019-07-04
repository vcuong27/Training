/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#ifndef  _GAME_RESOURCE_MGR_H_
#define  _GAME_RESOURCE_MGR_H_
#include "game_config.h"

using namespace rapidjson;

enum class ResourceType
{
	RESOURCE_NULL,
	RESOURCE_FONT,
	RESOURCE_AUDIO,
	RESOURCE_IMAGE
};

class ResourceMgr : public CSingleton < ResourceMgr >
{
public:
	ResourceMgr();
	~ResourceMgr();

	void initialize();
	void exit();
	void pause();
	void resume();
	void update(float deltaTime);

	Node* loadUI(const char* name);
	void setPath(std::string path);


	std::string getPath()
	{
		return m_path;
	}

private:
	std::string m_path;

	void parseJson(Node* node, const char* name);
	void parseNode(Node& node, rapidjson::Value& jsonValue);

	Node* parseJson(rapidjson::Value& jsonValue);
	Sprite* parseSprite(rapidjson::Value& jsonValue);
	Layer* parseLayer(rapidjson::Value& jsonValue);
	Label* parseLabel(rapidjson::Value& jsonValue);
	Menu* parseMenu(rapidjson::Value& jsonValue);
	MenuItemImage* parseMenuItemImage(rapidjson::Value& jsonValue);

};

#endif

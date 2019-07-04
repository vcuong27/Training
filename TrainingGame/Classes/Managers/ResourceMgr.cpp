/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "ResourceMgr.h"

/******************
*** Object Type ***
******************/

static const char* GAME_JSON_TYPE_MENU = "menu";
static const char* GAME_JSON_TYPE_MENU_ITEM = "menuItemImage";
static const char* GAME_JSON_TYPE_LABEL = "label";
static const char* GAME_JSON_TYPE_SPRITE = "sprite";
static const char* GAME_JSON_TYPE_LAYER = "layer";
static const char* GAME_JSON_TYPE_NODE = "node";

/******************
*** Json string ***
******************/
static const char* GAME_JSON_TAG = "tag";
static const char* GAME_JSON_ORDER = "order";
static const char* GAME_JSON_TYPE = "type";
static const char* GAME_JSON_SCALE = "scale";
static const char* GAME_JSON_NAME = "name";
static const char* GAME_JSON_TEXT = "text";
static const char* GAME_JSON_FONT = "fontPath";
static const char* GAME_JSON_FONTSIZE = "fontSize";
static const char* GAME_JSON_IMAGE = "image";
static const char* GAME_JSON_POSITION = "position";
static const char* GAME_JSON_ANCHO = "anchor";
static const char* GAME_JSON_SIZE = "size";
static const char* GAME_JSON_CHILD = "child";
static const char* GAME_JSON_TOUCHABLE = "touchable";
static const char* GAME_JSON_VISIBLE = "visible";
static const char* GAME_JSON_DESCRIPTION = "description";


/******************
*** define ***
******************/
#define GAME_JSON_GET_TAG(jsonObj) 			jsonObj[GAME_JSON_TAG]		.GetInt()
#define GAME_JSON_GET_ORDER(jsonObj) 		jsonObj[GAME_JSON_ORDER]	.GetInt()
#define GAME_JSON_GET_TYPE(jsonObj) 		jsonObj[GAME_JSON_TYPE]		.GetString()
#define GAME_JSON_GET_SCALE(jsonObj) 		jsonObj[GAME_JSON_SCALE]	.GetDouble()
#define GAME_JSON_GET_NAME(jsonObj) 		jsonObj[GAME_JSON_NAME]		.GetString()
#define GAME_JSON_GET_TEXT(jsonObj) 		jsonObj[GAME_JSON_TEXT]		.GetString()
#define GAME_JSON_GET_FONT(jsonObj) 		jsonObj[GAME_JSON_FONT]		.GetString()
#define GAME_JSON_GET_FONTSIZE(jsonObj) 	jsonObj[GAME_JSON_FONTSIZE]	.GetInt()
#define GAME_JSON_GET_IMAGE(jsonObj) 		jsonObj[GAME_JSON_IMAGE]	.GetString()
#define GAME_JSON_GET_POS(jsonObj)			Vec2(jsonObj[GAME_JSON_POSITION][0].GetInt(), jsonObj[GAME_JSON_POSITION][1].GetInt())
#define GAME_JSON_GET_ANCHO(jsonObj) 		Vec2(jsonObj[GAME_JSON_ANCHO][0].GetDouble(), jsonObj[GAME_JSON_ANCHO][1].GetDouble())
#define GAME_JSON_GET_SIZE(jsonObj) 		Size(jsonObj[GAME_JSON_SIZE][0].GetInt(), jsonObj[GAME_JSON_SIZE][1].GetInt())
#define GAME_JSON_GET_CHILD(jsonObj) 		jsonObj[GAME_JSON_CHILD]
#define GAME_JSON_GET_TOUCHABLE(jsonObj) 	jsonObj[GAME_JSON_TOUCHABLE]	.GetBool()
#define GAME_JSON_GET_VISIBLE(jsonObj) 		jsonObj[GAME_JSON_VISIBLE]		.GetBool()
#define GAME_JSON_GET_DESCRIPTION(jsonObj) 	jsonObj[GAME_JSON_DESCRIPTION]	.GetString()


#define GAME_JSON_HAS_TAG(jsonObj)			jsonObj.HasMember(GAME_JSON_TAG)
#define GAME_JSON_HAS_ORDER(jsonObj) 		jsonObj.HasMember(GAME_JSON_ORDER)
#define GAME_JSON_HAS_TYPE(jsonObj) 		jsonObj.HasMember(GAME_JSON_TYPE)
#define GAME_JSON_HAS_SCALE(jsonObj)		jsonObj.HasMember(GAME_JSON_SCALE)
#define GAME_JSON_HAS_NAME(jsonObj) 		jsonObj.HasMember(GAME_JSON_NAME)
#define GAME_JSON_HAS_TEXT(jsonObj) 		jsonObj.HasMember(GAME_JSON_TEXT)
#define GAME_JSON_HAS_FONT(jsonObj) 		jsonObj.HasMember(GAME_JSON_FONT)
#define GAME_JSON_HAS_FONTSIZE(jsonObj) 	jsonObj.HasMember(GAME_JSON_FONTSIZE)
#define GAME_JSON_HAS_IMAGE(jsonObj) 		jsonObj.HasMember(GAME_JSON_IMAGE)
#define GAME_JSON_HAS_POS(jsonObj)			jsonObj.HasMember(GAME_JSON_POSITION)
#define GAME_JSON_HAS_CHILD(jsonObj) 		jsonObj.HasMember(GAME_JSON_CHILD)
#define GAME_JSON_HAS_TOUCHABLE(jsonObj) 	jsonObj.HasMember(GAME_JSON_TOUCHABLE)
#define GAME_JSON_HAS_ANCHO(jsonObj)		jsonObj.HasMember(GAME_JSON_ANCHO)
#define GAME_JSON_HAS_SIZE(jsonObj)			jsonObj.HasMember(GAME_JSON_SIZE)
#define GAME_JSON_HAS_VISIBLE(jsonObj)		jsonObj.HasMember(GAME_JSON_VISIBLE)
#define GAME_JSON_HAS_DESCRIPTION(jsonObj)	jsonObj.HasMember(GAME_JSON_DESCRIPTION)


ResourceMgr::ResourceMgr()
{
}


ResourceMgr::~ResourceMgr()
{
}

void ResourceMgr::initialize()
{
}

void ResourceMgr::exit()
{
}

void ResourceMgr::pause()
{
}

void ResourceMgr::resume()
{
}

void ResourceMgr::update(float deltaTime)
{
}

void ResourceMgr::setPath(std::string path)
{
	m_path = path;
	std::vector<std::string> resDirOrders;
	resDirOrders.push_back(m_path + "sound");
	resDirOrders.push_back(m_path + "layout");
	resDirOrders.push_back(m_path + "image");
	resDirOrders.push_back(m_path + "fonts");
	FileUtils::getInstance()->setSearchPaths(resDirOrders);
}

Node * ResourceMgr::loadUI(const char* name)
{
	Node *temp = new Node();
	parseJson(temp, name);

	return temp;
}

void ResourceMgr::parseJson(Node* node, const char* name)
{
	std::string file = name;
	std::string json = CCFileUtils::sharedFileUtils()->getStringFromFile(file);
	Document document;
	document.Parse(json.c_str());
	for (rapidjson::Value::MemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr)
	{
		node->addChild(parseJson(itr->value));
	}
}

Node * ResourceMgr::parseJson(rapidjson::Value& jsonValue)
{
	GAME_ASSERT(GAME_JSON_HAS_TYPE(jsonValue), "\"type\" of Object must be set in json ");

	std::string temp = GAME_JSON_GET_TYPE(jsonValue);
	if (temp.compare(GAME_JSON_TYPE_LABEL) == 0) {
		return parseLabel(jsonValue);
	}
	else if (temp.compare(GAME_JSON_TYPE_SPRITE) == 0) {
		return parseSprite(jsonValue);
	}
	else if (temp.compare(GAME_JSON_TYPE_LAYER) == 0) {
		return parseLayer(jsonValue);
	}
	else if (temp.compare(GAME_JSON_TYPE_MENU) == 0) {
		return parseMenu(jsonValue);
	}
	else if (temp.compare(GAME_JSON_TYPE_MENU_ITEM) == 0) {
		return parseMenuItemImage(jsonValue);
	}
	else if (temp.compare(GAME_JSON_TYPE_NODE) == 0) {
		//return parseNode(jsonValue);
	}
	return nullptr;
}


void ResourceMgr::parseNode(Node& node, rapidjson::Value& jsonValue)
{
	if (GAME_JSON_HAS_TAG(jsonValue))
		node.setTag(GAME_JSON_GET_TAG(jsonValue));
	if (GAME_JSON_HAS_NAME(jsonValue))
		node.setName(GAME_JSON_GET_NAME(jsonValue));
	if (GAME_JSON_HAS_POS(jsonValue))
		node.setPosition(GAME_JSON_GET_POS(jsonValue));
	if (GAME_JSON_HAS_SCALE(jsonValue))
		node.setScale(GAME_JSON_GET_SCALE(jsonValue));
	if (GAME_JSON_HAS_ANCHO(jsonValue))
		node.setAnchorPoint(GAME_JSON_GET_ANCHO(jsonValue));
	if (GAME_JSON_HAS_SIZE(jsonValue))
		node.setContentSize(GAME_JSON_GET_SIZE(jsonValue));
	if (GAME_JSON_HAS_VISIBLE(jsonValue))
	{
		auto vissible = GAME_JSON_GET_VISIBLE(jsonValue);
		node.setVisible(vissible);
	}

	if (GAME_JSON_HAS_CHILD(jsonValue))
	{
		auto& child = GAME_JSON_GET_CHILD(jsonValue);
		for (rapidjson::Value::MemberIterator itr = child.MemberBegin(); itr != child.MemberEnd(); ++itr)
		{
			rapidjson::Value& chil = itr->value;
			if (GAME_JSON_HAS_ORDER(chil))
				node.addChild(parseJson(chil), GAME_JSON_GET_ORDER(chil));
			else
				node.addChild(parseJson(chil));
		}
	}
}


Sprite* ResourceMgr::parseSprite(rapidjson::Value& jsonValue)
{
	auto sprite = Sprite::create();
	if (GAME_JSON_HAS_IMAGE(jsonValue))
		sprite->initWithFile(GAME_JSON_GET_IMAGE(jsonValue));
	else
		sprite->initWithFile(GAME_DEFAUL_IMAGE);

	parseNode(*sprite, jsonValue);
	return sprite;
}

Layer * ResourceMgr::parseLayer(rapidjson::Value & jsonValue)
{
	auto layer = Layer::create();
	parseNode(*layer, jsonValue);
	return layer;
}

Label * ResourceMgr::parseLabel(rapidjson::Value & jsonValue)
{
	std::string text = "layer";
	std::string fontpath = GAME_DEFAUL_FONT;
	int fontSize = GAME_DEFAUL_FONT_SIZE;
	if (GAME_JSON_HAS_TEXT(jsonValue))
		text = GAME_JSON_GET_TEXT(jsonValue);
	if (GAME_JSON_HAS_FONT(jsonValue))
		fontpath = GAME_JSON_GET_FONT(jsonValue);
	if (GAME_JSON_HAS_FONTSIZE(jsonValue))
		fontSize = GAME_JSON_GET_FONTSIZE(jsonValue);

	auto label = Label::createWithTTF(text, fontpath, fontSize);
	parseNode(*label, jsonValue);
	return label;
}

Menu * ResourceMgr::parseMenu(rapidjson::Value & jsonValue)
{
	auto menu = Menu::create();
	parseNode(*menu, jsonValue);
	return menu;
}

MenuItemImage * ResourceMgr::parseMenuItemImage(rapidjson::Value & jsonValue)
{
	auto itemImage = MenuItemImage::create();
	if (GAME_JSON_HAS_IMAGE(jsonValue))
	{
		auto spr = Sprite::create(GAME_JSON_GET_IMAGE(jsonValue));
		itemImage->setNormalImage((Node*)spr);
	}
	else
	{
		auto spr = Sprite::create(GAME_DEFAUL_IMAGE);
		itemImage->setNormalImage((Node*)spr);
	}
	parseNode(*itemImage, jsonValue);
	return itemImage;
}

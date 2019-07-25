#include "Person.h"
#include "GameDefines.h"

Person::Person()
{
	Init();
}

void Person::Init()
{
	mAnimation = new Animation(nullptr);
	Vector2 screen = Config::getInstance()->getScreenSize();

	SpriteSheet* spriteSheet = new SpriteSheet(nullptr, Vector2(436, 72), Vector2(109,72));
	spriteSheet->setTexture(SMResource->GetTextureByKey("cupid"));
	spriteSheet->setModel(SMResource->GetModelByKey("Rect"));
	spriteSheet->setGLProgram(SMResource->GetProgramByKey("SpriteShader"));
	spriteSheet->setLenghTime(0.13f);
	//spriteSheet->setPosition(Vector2(screen.x, screen.y));

	//spriteSheet->setScale(Vector2(1.0f, 1.0f));
	
	mAnimation->AddSpriteAnimation(Animation::STATE_RUN, spriteSheet);
	SetPostion(Vector2(screen.x / 2, screen.y / 2 + 77));
	//float scaleFactor = 0.1f;
	SetScale(Vector2(0.1f, 0.1f));
	SetObjectDistance(Vector2(109 ,72));
	SetAnimation(Animation::STATE_RUN);
}

void Person::update(float dt)
{
	mPostion += vecVelocity;
	SetPostion(mPostion);
	//moving ./...
	Object::update(dt);
}

Person::~Person()
{
}
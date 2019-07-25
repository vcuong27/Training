#include <tchar.h>
#include "esUtil.h"
#include "esUtil_win.h"
#include "..\..\libraries\GraphicEngine\src\utils\FileUtils.h"

int screenWidth = 640;
int screenHeight = 640;

#include "../../libraries/GraphicEngine/src/Config.h"

#include "GameStates\GameStatebase.h"
#include "ResourceManagers.h"
#include "SceneManagers.h"


int Init ( ESContext *esContext )
{
	auto fu = FileUtils::create();

	Config::getInstance()->setScreenSize(Vector2(screenWidth, screenHeight));
	
#ifdef WIN32
	fu->addSearchPath("../data");
#elif ANDROID
	fu->addSearchPath("/sdcard/gangof4/"); //TODO: only for example, change this later
#endif
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );

	ResourceManagers::GetInstance()->InitResources("");
	SceneManagers::GetInstance();
	GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Play);
	
	return true;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Draw();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	GameStateMachine::GetInstance()->PerformStateChange();

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	printf("%5d\n", key);
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(key , bIsPressed);
	
}

Vector2 ConvertToLocationDesign(Vector2& pos)
{
	return Vector2(pos.x, Config::getInstance()->getScreenSize().y - pos.y); 
}

void TouchActionDown(ESContext *esContext, int x, int y)
{
	Vector2 locationMouse = ConvertToLocationDesign(Vector2(x , y));

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(locationMouse.x, locationMouse.y, true);
}
void TouchActionUp(ESContext *esContext, int x, int y)
{
	Vector2 locationMouse = ConvertToLocationDesign(Vector2(x , y));
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(locationMouse.x, locationMouse.y, false);
}
void TouchActionMove(ESContext *esContext, int x, int y)
{
	Vector2 locationMouse = ConvertToLocationDesign(Vector2(x , y));

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(locationMouse.x, locationMouse.y, true);
}
void CleanUp()
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", screenWidth, screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (!Init(&esContext))
	{
		return 0;
	}

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseDownFunc( &esContext, TouchActionDown);
	esRegisterMouseUpFunc( &esContext, TouchActionUp);
	esRegisterMouseMoveFunc( &esContext, TouchActionMove);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	//MemoryDump();
	//printf("Press any key...\n");
	//_getch();

	return 0;
}


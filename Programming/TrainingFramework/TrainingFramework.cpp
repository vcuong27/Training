// NewTrainingFramework.cpp : Defines the entry point for the console application.
//
//#ifdef WIN32
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Application.h"

GLint screenWidth = 640;
GLint screenHeight = 720;


GLint Init ( ESContext *esContext )
{
	Application::GetInstance()->Init();
	return 0;
}

void Draw ( ESContext *esContext )
{
	Application::GetInstance()->Render();
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, GLfloat deltaTime )
{
	Application::GetInstance()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bbIsPresseded)
{
	Application::GetInstance()->HandleKeyEvent(key, bbIsPresseded);
}

void Mouse (ESContext *esContext, GLint x, GLint y, bool bbIsPresseded)
{
	Application::GetInstance()->HandleTouchEvent(x,y,bbIsPresseded);
}

void CleanUp()
{
	Application::GetInstance()->Exit();
	Application::FreeInstance();
}

GLint _tmain(GLint argc, _TCHAR* argv[])
{

	ESContext esContext;
    esInitContext ( &esContext );
	esCreateWindow ( &esContext, "Hello Triangle", screenWidth, screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseFunc ( &esContext, Mouse);
	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

//#endif
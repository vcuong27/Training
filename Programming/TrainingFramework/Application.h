#pragma once
#ifdef WIN32
#include "../Utilities/utilities.h" 
#else
#include "GameCommon.h"
#include "../../Utilities/Math.h"
#include "Singleton.h"
#endif

class Application : public CSingleton<Application>
{
public:
	Application(void);
	~Application(void);
	void		Init();
	void		Update( GLfloat deltaTime);
	void		Render();
	void		HandleKeyEvent(unsigned char key, bool bIsPresseded);
	void		HandleTouchEvent(GLint x, GLint y, bool bIsPresseded);
	void		Exit();

};


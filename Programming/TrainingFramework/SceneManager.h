#pragma once
#ifdef WIN32
	#include "../Utilities/utilities.h" 
#else
#include "../../Utilities/Math.h"
#include "Singleton.h"
#include<list>
#endif



class BaseObject;
class Camera;

class SceneManager : public CSingleton<SceneManager>
{
private:
	std::list<BaseObject *> m_Object;
	Camera* m_pCamera;

public:
	SceneManager();
	~SceneManager();

	void					addObject(BaseObject *obj);
	void					addListObject(std::list<BaseObject *> list_obj);
	void 					removeObject(BaseObject* obj);
	std::list<BaseObject *> getListObject();
	void 					clearObject();
	void 					Draw();
	void 					Update(GLfloat deltatime);
	void 					keypress(int key);
	Camera*  				GetCamera();
	void  					SetCamera(Camera* cam);
};
#ifndef __SCENE_MANAGERS__
#define __SCENE_MANAGERS__
#include "core/Singleton.h"
#include "GraphicHeaders.h"
#include "objects/Object.h"
#include <vector>

class SceneManagers : public CSingleton<SceneManagers>
{
public:
	SceneManagers() {};
	~SceneManagers() {};
	//Vector2 getPostionCupid();
	void AddGameObjectToScene(Object *object);
	void SetNewPostionForBullet();
protected:
	std::vector<Object *> mVectorObject;
private:
};

#endif //__SCENE_MANAGERS__
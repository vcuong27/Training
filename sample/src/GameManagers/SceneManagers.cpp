#include "SceneManagers.h"
#include "objects/Cupid.h"

/*Vector2 SceneManagers::getPostionCupid()
{
	for (auto  it : mVectorObject)
	{
		if (it->GetName() == Cupid::k_name)
		{
			return it->GetPostion();
		}
	}
}*/

void SceneManagers::AddGameObjectToScene(Object *object)
{
	mVectorObject.push_back(object);
}

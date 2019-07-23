#include "SceneManager.h"

#include "Shaders.h"
#include "Models.h"
#include "Texture.h"
#include "BaseObject.h"
#include "Camera.h"

SceneManager::SceneManager()
{
	//Vector3 CameraPos(0,0,-1);
	//Vector3 TargetPos(0,0,0);
	//float fFovY = 0.7f;
	//m_pCamera = new Camera();
	//m_pCamera->Init(CameraPos,TargetPos,fFovY,1.0,1.0,5000.0,1.0);
}

SceneManager::~SceneManager()
{
	for (std::list<BaseObject*>::iterator it = m_Object.begin(); it != m_Object.end(); it++)
		delete (*it);
	m_Object.clear();
	//delete m_pCamera;
}


void SceneManager::addObject(BaseObject* obj)
{
	obj->SetCamera(m_pCamera);
	m_Object.push_back(obj);
	LOGI("count = %d\n", m_Object.size());
}

void SceneManager::addListObject(std::list<BaseObject *> list_obj)
{
	for (std::list<BaseObject*>::iterator it = list_obj.begin(); it != list_obj.end(); it++)
	{
		(*it)->SetCamera(m_pCamera);
		m_Object.push_back(*it);
	}
}

std::list<BaseObject *> SceneManager::getListObject()
{
	return m_Object;
}

void SceneManager::removeObject(BaseObject* obj)
{
	m_Object.remove(obj);
}

void SceneManager::clearObject()
{
	m_Object.clear();
}

void SceneManager::Draw()
{
	for (std::list<BaseObject*>::iterator it = m_Object.begin(); it != m_Object.end(); it++)
		(*it)->Draw();

}

void SceneManager::Update(GLfloat deltatime)
{
	for (std::list<BaseObject*>::iterator it = m_Object.begin(); it != m_Object.end(); it++)
		(*it)->Update(deltatime);
}


void SceneManager::keypress(int key)
{
	Vector3 m_Vec3Position = m_pCamera->GetLocation();
	Matrix rY;
	Vector4 pos= Vector4(m_Vec3Position.x,m_Vec3Position.y,m_Vec3Position.z,1.0);
	Vector4 temp;
	switch (key)
	{
	case  KEY_RIGHT :

		rY.SetRotationY(1 * COLUMN);
		pos = pos * rY;
		//temp = pos;
		//temp.Multi(rY);
		m_Vec3Position = Vector3(pos.x,pos.y,pos.z);
		m_pCamera->SetLocation(m_Vec3Position);

		break;
	case  KEY_LEFT  :

		rY.SetRotationY(-1 * COLUMN);
		pos = pos * rY;
		//temp = pos;
		//temp.Multi(rY);
		m_Vec3Position = Vector3(pos.x,pos.y,pos.z);
		m_pCamera->SetLocation(m_Vec3Position);
		break;
	}
}

Camera*  SceneManager::GetCamera()
{
	return m_pCamera;
}

void SceneManager::SetCamera(Camera* cam)
{
	//delete m_pCamera;
	m_pCamera = cam;
}
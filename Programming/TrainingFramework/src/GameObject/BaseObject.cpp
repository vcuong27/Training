#include "BaseObject.h"


BaseObject::BaseObject()
{
	m_Id = 0;
	m_Name = "name";
	m_Vec3Position = Vector3(0, 0, 0);
	m_Vec3Scale = Vector3(1, 1, 1);
	m_Vec3Rotation = Vector3(0, 0, 0);
	m_pModel = nullptr;
	m_pShader = nullptr;
	m_pCamera = nullptr;
	m_texture = nullptr;
}

BaseObject::~BaseObject()
{
}

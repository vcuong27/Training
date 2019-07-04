#pragma once
#ifdef WIN32
	#include "../Utilities/utilities.h" 
#else
#include "../../Utilities/Math.h"
#include "GameCommon.h"
#include<list>
#include <string>
#endif

class Shaders;
class Models;
class Camera;
class BaseObject
{

private:
	GLint			m_Id;
	std::string		m_Name;

protected:
	Vector3			m_Vec3Position;
	Vector3			m_Vec3Scale;
	Vector3			m_Vec3Rotation;

	Models			*m_pModel;
	Shaders			*m_pShader;
	Camera			*m_pCamera;
public:
	BaseObject();
	virtual ~BaseObject();

	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Update(GLfloat deltaTime) = 0;

	// get - set
	void			SetObjectID(GLuint id)		{ m_Id		= id; }
	GLint			GetObjectID(GLuint id)		{ return	m_Id; }

	void			SetName(std::string name)	{ m_Name	= name; }
	std::string		GetName()					{ return	m_Name;  }

	void			Set3DPosition(Vector3 pos)	{ m_Vec3Position	= pos; }
	Vector3			Get3DPosition()				{ return			m_Vec3Position; }

	void			Set3DScale(Vector3 sca)		{ m_Vec3Scale		= sca; }
	Vector3			Get3DScale()				{ return			m_Vec3Scale; }

	void			Set3DRotation(Vector3 ros)	{ m_Vec3Rotation	= ros; }
	Vector3			Get3DRotation()				{ return			m_Vec3Rotation; }

	void			SetCamera(Camera *cam)		{m_pCamera	= cam;}

	void			SetModels(Models* mod)		{m_pModel	= mod;}

	void			SetShaders(Shaders* sha)	{m_pShader	= sha;}

};


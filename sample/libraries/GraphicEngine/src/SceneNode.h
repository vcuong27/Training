#pragma once

#include <vector>
#include "GLProgram.h"
#include "Model.h"
#include "Texture.h"
#include "Math.h"
#include "SEvent.h"
#include <list>

class SceneNode;
typedef std::list<SceneNode*> SceneNodeList;

class SceneNode
{
public:
	SceneNode(SceneNode* parent);
	~SceneNode();
	virtual void	draw();
	virtual void	update(float dt);
	virtual SceneNode*	getParent() const;
	virtual const	SceneNodeList& getChildren() const;
	virtual SceneNode*	getChildrenFromId(GLint id, bool searchchildren = false);
	virtual SceneNode*	getChildrenFromName(std::string name, bool searchchildren = false);
	virtual void	addChild(SceneNode* child);
	virtual void	removeChild(SceneNode* child);
	virtual void	remove();
	virtual bool	isVisible() const;
	virtual void	setVisible(bool visible);
	virtual bool	isEnabled() const;
	virtual void	setEnabled(bool enabled);
	virtual bool	bringToFront(SceneNode* element);
	virtual bool	sendToBack(SceneNode* child);
	virtual bool	OnEvent(const SEvent& event);
	
	void			setPosition(const Vector2& pos);
	const Vector2&	getPosition() const;
	void			setScale(const Vector2& scale);
	const Vector2&	getScale() const;
	void 			setRotation(const Vector2& rotation);
	const Vector2&	getRotation() const;
	void  			setID(GLuint id);
	const GLint		getID();
	void  			setName(std::string name);
	const std::string getName();
	void  			setTexture(Texture* texture);
	const Texture*	getTexture() const;
	void  			setGLProgram(GLProgram* program);
	const GLProgram* getGLProgram() const;
	void  			setModel(Model* model);
	const Model*	getModel() const;
	Vector2 SceneNode::convertToGLPosition(const Vector2& screenPos);
	void			setRotationByAngle(float angle);

protected:
	float				m_Angle; 
	int					_Id;
	std::string			_Name;
	bool				_IsVisible;
	bool				_IsEnabled;
	GLProgram*			_shaderProgram;
	Model*				_rectModel;
	Texture*			_texture;
	Vector2				_pos;
	Matrix 				_worldMatrix;
	Vector2 			_scale;
	Vector2 			_rotation;
	SceneNodeList		_children;
	SceneNode*			_parent;

	void addChildToEnd(SceneNode* child);
	void updateWorldMatrix();

};

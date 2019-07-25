#include "SceneNode.h"
#include "Config.h"
SceneNode::SceneNode(SceneNode* parent):
	_pos(Vector2(0.0f,0.0f)),
	_scale(Vector2(1.f, 1.f)),
	_shaderProgram(nullptr),
	_IsEnabled(true),
	_IsVisible(true),
	m_Angle(0.0f)
{
	if (parent)
	{
		parent->addChildToEnd(this);
	}
}

SceneNode::~SceneNode() {
	SceneNodeList::iterator it = _children.begin();
	for (; it != _children.end(); ++it)
	{
		(*it)->_parent = 0;
		//(*it)->drop();
		delete (*it);
	}
}

void SceneNode::draw() {
	if ( isVisible() )
	{
		SceneNodeList::iterator it = _children.begin();
		for (; it != _children.end(); ++it)
			(*it)->draw();
	}
}

void SceneNode::update(float dt) {
	if ( isVisible() )
	{
		SceneNodeList::iterator it = _children.begin();
		for (; it != _children.end(); ++it)
			(*it)->update(dt);
	}
}


void SceneNode::setPosition(const Vector2& pos) {
	_pos = pos;
	updateWorldMatrix();
}

const Vector2& SceneNode::getPosition() const{
	return _pos;
}

void SceneNode::setScale(const Vector2& scale) {
	_scale = scale;
	updateWorldMatrix();
}

const Vector2& SceneNode::getScale() const{
	return _scale;
}

void SceneNode::setRotation(const Vector2& rotation) {
	_rotation = rotation;
	updateWorldMatrix();
}

const Vector2& SceneNode::getRotation() const{
	return _rotation;
}

Vector2 SceneNode::convertToGLPosition(const Vector2& screenPos)
{
	Vector2 screenSize = Config::getInstance()->getScreenSize();

	float gl_y = -1 + 2 * screenPos.y / screenSize.y;
	float gl_x = -1 + 2 * screenPos.x / screenSize.x;

	return Vector2(gl_x, gl_y);
}

void SceneNode::setID(GLuint id) {
	_Id = id;
}

const GLint SceneNode::getID() {
	return _Id;
}

void SceneNode::setName(std::string name) { 
	_Name	= name; 
}
const std::string SceneNode::getName() { 
	return	_Name;  
}
void SceneNode::setTexture(Texture* texture) {
	_texture = texture;
};
const Texture* SceneNode::getTexture() const {
	return _texture;
}
void SceneNode::setGLProgram(GLProgram* program) {
	_shaderProgram = program;
};
const GLProgram* SceneNode::getGLProgram() const {
	return _shaderProgram;
}

void SceneNode::setModel(Model* model) {
	_rectModel = model;
};
const Model* SceneNode::getModel() const {
	return _rectModel;
}


SceneNode* SceneNode::getParent() const {
	return _parent;
}

const SceneNodeList& SceneNode::getChildren() const {
	return _children;
}

SceneNode* SceneNode::getChildrenFromId(GLint id, bool searchchildren ) {
	SceneNode* e = 0;
	SceneNodeList::iterator it = _children.begin();
	for (; it != _children.end(); ++it)
	{
		if ((*it)->getID() == id)
			return (*it);

		if (searchchildren)
			e = (*it)->getChildrenFromId(id, true);

		if (e)
			return e;
	}
	return e;
}

SceneNode* SceneNode::getChildrenFromName(std::string name, bool searchchildren) {
	SceneNode* e = 0;
	SceneNodeList::iterator it = _children.begin();
	for (; it != _children.end(); ++it)
	{
		if ((*it)->getName() == name)
			return (*it);

		if (searchchildren)
			e = (*it)->getChildrenFromName(name, true);

		if (e)
			return e;
	}
	return e;
}

void SceneNode::addChild(SceneNode* child) {
	addChildToEnd(child);
}

void SceneNode::removeChild(SceneNode* child) {
	SceneNodeList::iterator it = _children.begin();
	for (; it != _children.end(); ++it)
		if ((*it) == child)
		{
			(*it)->_parent = 0;
			//(*it)->drop();
			_children.erase(it);
			return;
		}
}

void SceneNode::remove() {
	if (_parent)
		_parent->removeChild(this);
}

bool SceneNode::isVisible() const {
	return _IsVisible;
}

void SceneNode::setVisible(bool visible) {
	_IsVisible = visible;
}

bool SceneNode::isEnabled() const {
	if ( getParent() )
		return getParent()->isEnabled();
	return _IsEnabled;
}

void SceneNode::setEnabled(bool enabled) {
	_IsEnabled = enabled;
}

bool SceneNode::bringToFront(SceneNode* element) {
	SceneNodeList::iterator it = _children.begin();
	for (; it != _children.end(); ++it)
	{
		if (element == (*it))
		{
			_children.erase(it);
			_children.push_back(element);
			return true;
		}
	}
	return false;
}

bool SceneNode::sendToBack(SceneNode* child) {
	SceneNodeList::iterator it = _children.begin();
	if (child == (*it))	// already there
		return true;
	for (; it != _children.end(); ++it)
	{
		if (child == (*it))
		{
			_children.erase(it);
			_children.push_front(child);
			return true;
		}
	}
	return false;
}

bool SceneNode::OnEvent(const SEvent& event)
{
	return _parent ? _parent->OnEvent(event) : false;
}

void SceneNode::addChildToEnd(SceneNode* child) {
	if (child)
	{
		//child->grab(); // prevent destruction when removed
		child->remove();
		child->_parent = this;
		_children.push_back(child);
	}
}

void SceneNode::setRotationByAngle(float angle)
{
	m_Angle = angle;
	updateWorldMatrix();
}

void SceneNode::updateWorldMatrix() {
	Matrix S, R, T;
	Matrix Rx, Ry, Rz;
	Rx.SetIdentity(); Ry.SetIdentity(); Rz.SetIdentity();

	Rx.SetRotationX(0.0f);
	Ry.SetRotationY(0.0f);
	Rz.SetRotationZ(m_Angle);
	R = Rz*Rx*Ry;
	S.SetScale(Vector3(_scale.x, _scale.y, 1.f));

	Vector2 glPos = convertToGLPosition(_pos);
	T.SetTranslation(Vector3(glPos.x, glPos.y, 0.f));

	_worldMatrix = S*R*T;
}
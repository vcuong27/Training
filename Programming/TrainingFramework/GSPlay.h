#pragma once
#include "gamestatebase.h"

class Texture;
class Shaders;
class Models;
class Pieces;
class GameObject;
class Camera;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents(GameStateMachine* game);
	void HandleKeyEvents(GameStateMachine* game, GLint key, bool bIsPressed);
	void HandleTouchEvents(GameStateMachine* game, GLint x, GLint y, bool bIsPressed);
	void Update(GameStateMachine* game, GLfloat deltaTime);
	void Draw(GameStateMachine* game);

private:
	Camera*						m_pCam;
	int							m_board[MAX_COL][MAX_ROW];
	std::list<GameObject*>		m_listObj;
	std::list<GameObject*>		m_list_active_Obj;
	Pieces*		mPieces;
	int			mPosX, mPosY;				// Position of the piece that is falling down
	int			mPiece, mRotation;			// Kind and rotation the piece that is falling down
	int			m_PPX;

	int			GetRand (int pA, int pB);
	void		CreateNewPiece();
	void		RostaionPiece();
	
	bool		IsPossibleMovement (int pX, int pY, int pPiece, int pRotation);
	bool		IsFreeBlock (int pX, int pY);
	bool		IsGameOver();
	void		StorePiece (int pX, int pY, int pPiece, int pRotation);

	void		DeletePossibleLines ();
	void		DeleteLine (int pY);

	GLfloat		timer;
	bool		gameOver;
	int			zzzz;
};


#include "stdafx.h"
#include "GSPlay.h"
#include <time.h>
#include "Pieces.h"
#include "Shaders.h"
#include "Models.h"
#include "Texture.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"

extern GLint screenWidth;
extern GLint screenHeight;

#define SManager SceneManager::GetInstance()
#define RsManager ResourceManager::GetInstance()

GSPlay::GSPlay()
{

}


GSPlay::~GSPlay()
{
	
}


void GSPlay::Init()
{
	srand ((unsigned int) time(NULL));

	for(int ii=0;ii< MAX_COL;ii++)
		for(int jj = 0; jj < MAX_ROW; jj++)
			m_board[ii][jj] = 0;

	Vector3 CameraPos(0,18,30);
	Vector3 TargetPos(0,6,0);
	float fFovY = 0.7f;
	m_pCam = new Camera();
	m_pCam->Init(CameraPos,TargetPos,fFovY, (GLfloat) screenWidth/screenHeight, 1.0f, 5000.0f, 1.0f);
	SManager->SetCamera(m_pCam);

#ifdef ANDROID
	RsManager->Init("/sdcard/Resources/RM_android.txt");
#else
	RsManager->Init("../Resources/RM.txt");
#endif

	timer = 0;
	gameOver = false;
	zzzz = 0;

	Models* m_temp_mod		= RsManager->GetModels(0);
	Shaders* m_temp_shad	= RsManager->GetShaders(0);

	Vector3 m_temp_pos(0,0,0);
	Vector3 m_temp_ros(0,0,0);
	Vector3 m_temp_sca(1,1,1);

	GameObject* obj;
	for (int i = 0; i < MAX_COL; i++)
	{
		obj = new GameObject();
		obj->Set3DPosition(m_temp_pos);
		obj->Set3DRotation(m_temp_ros);
		obj->Set3DScale(m_temp_sca);
		obj->SetShaders(m_temp_shad);
		obj->SetModels(m_temp_mod);
		obj->Init();
		obj->Set2DPosition( i, MAX_ROW);
		SManager->addObject(obj);
	}

	CreateNewPiece();
}

void GSPlay::Exit()
{
	m_listObj.clear();
	LOGD("m_listObj.clear() \n");
	delete m_pCam;
	RsManager->FreeInstance();
	LOGD("ResourceManager::DestroyInstance()\n");
	SManager->FreeInstance();
	LOGD("SManager->DestroyInstance()\n");
}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents(GameStateMachine* game)
{

}

void GSPlay::HandleKeyEvents(GameStateMachine* game, GLint key, bool bIsPressed)
{
	if(!bIsPressed) return;

	Vector2 pos;
	switch (key)
	{
	case  KEY_RIGHT :
		if (IsPossibleMovement (mPosX + 1, mPosY, mPiece, mRotation))
		{
			SManager->keypress(key);
			LOGD("KEY_RIGHT %d \n", mPosX);
			zzzz ++;
			if(zzzz >= MAX_COL) zzzz = 0;
			mPosX ++;
			if(mPosX >= MAX_COL + m_PPX ) mPosX = m_PPX;
			for (std::list<GameObject*>::iterator it = m_list_active_Obj.begin(); it != m_list_active_Obj.end(); it++)
			{
				pos.x = (*it)->Get2DPosition().x;
				pos.y = (*it)->Get2DPosition().y;
				pos.x ++;
				if(pos.x>MAX_COL) pos.x = 0;
				(*it)->Set2DPosition(pos.x,pos.y);
			}
		}
		break;
	case  KEY_LEFT  :
		if (IsPossibleMovement (mPosX - 1, mPosY, mPiece, mRotation))
		{
			SManager->keypress(key);
			LOGD("KEY_LEFT\n");
			zzzz --;
			if(zzzz <0 ) zzzz = MAX_COL-1;
			mPosX --;
			if(mPosX < m_PPX ) mPosX = MAX_COL - 1 + m_PPX;
			for (std::list<GameObject*>::iterator it = m_list_active_Obj.begin(); it != m_list_active_Obj.end(); it++)
			{
				pos.x = (*it)->Get2DPosition().x;
				pos.y = (*it)->Get2DPosition().y;
				pos.x --;
				if(pos.x < 0) pos.x = MAX_COL - 1;
				(*it)->Set2DPosition(pos.x,pos.y);
			}
		}
		break;
	case KEY_DOWN:

		if (IsPossibleMovement (mPosX, mPosY + 1, mPiece, mRotation))
		{
			mPosY ++;
			for (std::list<GameObject*>::iterator it = m_list_active_Obj.begin(); it != m_list_active_Obj.end(); it++)
			{
				pos.x = (*it)->Get2DPosition().x;
				pos.y = (*it)->Get2DPosition().y;
				pos.y++;
				(*it)->Set2DPosition(pos.x,pos.y);
			}
		}
		break;

	case KEY_UP:
		if (IsPossibleMovement (mPosX, mPosY, mPiece, (mRotation + 1) % 4))
		{
			mRotation = (mRotation + 1) % 4;
			for (std::list<GameObject*>::iterator it = m_list_active_Obj.begin(); it != m_list_active_Obj.end(); it++)
			{
				SManager->removeObject(*it);
				m_listObj.remove(*it);
				delete (*it);
			}
			RostaionPiece();
		}
	case KEY_BACK:
		game->ChangeState(STATE_Menu);
	default:;
	}
}

void GSPlay::HandleTouchEvents(GameStateMachine* game, GLint x, GLint y, bool bIsPressed)
{

}

void GSPlay::Update(GameStateMachine* game, GLfloat deltaTime)
{
	SManager->Update(deltaTime);

	if( gameOver ) return;
	timer += deltaTime;
	if(timer > WAIT_TIME)
	{
		timer -= WAIT_TIME;

		if (IsPossibleMovement (mPosX, mPosY + 1, mPiece, mRotation))
		{
			mPosY ++;
			Vector2 pos;
			for (std::list<GameObject*>::iterator it = m_list_active_Obj.begin(); it != m_list_active_Obj.end(); it++)
			{
				pos.x = (*it)->Get2DPosition().x;
				pos.y = (*it)->Get2DPosition().y;
				pos.y++;
				(*it)->Set2DPosition(pos.x,pos.y);
			}
		}
		else
		{
			StorePiece (mPosX, mPosY, mPiece, mRotation);

			DeletePossibleLines ();

			if (IsGameOver())
			{
				gameOver = true;
			}
			else
				CreateNewPiece();
		}
	}
}

void GSPlay::Draw(GameStateMachine* game)
{
	SManager->Draw();
}


void GSPlay::DeleteLine (int pY)
{
	// Moves all the upper lines one row down
	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < MAX_COL; i++)
		{
			m_board[i][j] = m_board[i][j-1];
		}
	}	

	std::list<GameObject*>	m_listObj_temp;

	Vector2 vt ;

	for (std::list<GameObject*>::iterator it = m_listObj.begin(); it != m_listObj.end(); it++)
	{
		vt.x = (*it)->Get2DPosition().x;
		vt.y = (*it)->Get2DPosition().y;
		if (vt.y == pY)
		{
			m_listObj_temp.push_back(*it);
		}
	}

	for (std::list<GameObject*>::iterator it = m_listObj_temp.begin(); it != m_listObj_temp.end(); it++)
	{
		SManager->removeObject(*it);
		m_listObj.remove(*it);
		delete (*it);
	}

	for (std::list<GameObject*>::iterator it = m_listObj.begin(); it != m_listObj.end(); it++)
	{
		vt.x = (*it)->Get2DPosition().x;
		vt.y = (*it)->Get2DPosition().y;
		if (vt.y < pY)
			(*it)->Set2DPosition(vt.x,vt.y+1);
	}
}

void GSPlay::DeletePossibleLines ()
{
	for (int j = 0; j < MAX_ROW; j++)
	{
		int i = 0;
		while (i < MAX_COL)
		{
			if (m_board[i][j] != 1) break;
			i++;
		}

		if (i == MAX_COL) DeleteLine (j);
	}
}



bool GSPlay::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation)
{
	// Checks collision with pieces already stored in the board or the board limits
	// This is just to check the 5x5 blocks of a piece with the appropiate area in the board
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{	
			// Check if the piece is outside the limits of the board
			if (j1 > MAX_ROW - 1)
			{
				if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)
					return false;		
			}
			// Check if the piece have collisioned with a block already stored in the map
			if (j1 >= 0)	
			{
				if ((mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) &&
					(!IsFreeBlock (i1, j1))	)
					return false;
			}
		}
	}

	// No collision
	return true;
}

bool GSPlay::IsFreeBlock (int pX, int pY)
{
	if(pX >= MAX_COL) pX -= MAX_COL;
	if(pX < 0) pX += MAX_COL;

	if (m_board [pX][pY] == 0) return true; 
	else return false;
}

bool GSPlay::IsGameOver()
{
	//If the first line has blocks, then, game over
	for (int i = 0; i < MAX_COL; i++)
	{
		if (m_board[i][0] != 0) return true;
	}

	return false;
}

void GSPlay::StorePiece (int pX, int pY, int pPiece, int pRotation)
{
	int temp =0;
	// Store each block of the piece into the board
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{	
			// Store only the blocks of the piece that are not holes
			if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)	
			{
				temp = i1;
				if(i1 >= MAX_COL) temp -= MAX_COL;
				else
					if(i1 < 0) temp += MAX_COL;
				m_board[temp][j1] = 1;	
			}
		}
	}

	for(int ii=0;ii< MAX_COL;ii++)
	{
		//for(int jj = 0; jj < MAX_ROW; jj++)
		//LOGD("%d",m_board[ii][jj] );
		//LOGD("\n");
	}
}


void GSPlay::CreateNewPiece()
{
	//return;
	//GameObject* obj;


	mPiece			= GetRand (0, 6);;//mNextPiece;
	mRotation		= GetRand (0, 3);//mNextRotation;

	mPosX = m_PPX	= mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition (mPiece, mRotation);
	m_list_active_Obj.clear();

	mPosX += zzzz ;
	RostaionPiece();
	/*
	Models* m_temp_mod		= RsManager->GetModels(0);
	Shaders* m_temp_shad	= RsManager->GetShaders(0);

	Vector3 m_temp_pos(0,0,0);
	Vector3 m_temp_ros(0,0,0);
	Vector3 m_temp_sca(ZOOM_OBJ,ZOOM_OBJ,ZOOM_OBJ);

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			// Get the type of the block and draw it with the correct color
			if (mPieces->GetBlockType (mPiece, mRotation, j, i) != 0)
			{
				GameObject* obj = new GameObject();
				obj->Set3DPosition(m_temp_pos);
				obj->Set3DRotation(m_temp_ros);
				obj->Set3DScale(m_temp_sca);
				obj->SetShaders(m_temp_shad);
				obj->SetModels(m_temp_mod);
				obj->Init();
				obj->Set2DPosition(mPosX + i,mPosY + j);

				SManager->addObject(obj);
				m_listObj.push_back(obj);
				m_list_active_Obj.push_back(obj);
			}
		}
	}
	//Vector3 CameraPos(0,15,50);
	//SManager->GetCamera()->SetLocation(CameraPos);
	*/
}

void GSPlay::RostaionPiece()
{
	m_list_active_Obj.clear();
	GameObject* obj;
	Models* m_temp_mod		= RsManager->GetModels(0);
	Shaders* m_temp_shad	= RsManager->GetShaders(0);
	Vector3 m_temp_pos(0,0,0);
	Vector3 m_temp_ros(0,0,0);
	Vector3 m_temp_sca(ZOOM_OBJ,ZOOM_OBJ,ZOOM_OBJ);
	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			// Get the type of the block and draw it with the correct color
			if (mPieces->GetBlockType (mPiece, mRotation, j, i) != 0)
			{
				obj = new GameObject();
				obj->Set3DPosition(m_temp_pos);
				obj->Set3DRotation(m_temp_ros);
				obj->Set3DScale(m_temp_sca);
				obj->SetShaders(m_temp_shad);
				obj->SetModels(m_temp_mod);
				obj->Init();
				obj->Set2DPosition(mPosX + i,mPosY + j);
				SManager->addObject(obj);
				m_listObj.push_back(obj);
				m_list_active_Obj.push_back(obj);
			}
		}
	}
}


int GSPlay::GetRand (int pA, int pB)
{
	return rand () % (pB - pA + 1) + pA;
}
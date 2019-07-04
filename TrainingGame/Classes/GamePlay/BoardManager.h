#pragma once

#include "GameTile.h"
#include "GamePiece.h"
#include "base\Singleton.h"
#include <list>
using namespace std;


template <typename T>
T clip(const T& n, const T& lower, const T& upper) 
{
	return std::max(lower, std::min(n, upper));
}


template< class T > void SafeDelete(T*& pVal)
{
	if (pVal != NULL)
	{
		delete pVal;
		pVal = NULL;
	}
}

class BoardManager : public CSingleton<BoardManager>
{
public:
	//BoardManager();
	~BoardManager();

	GameTile m_allTiles[WIDTH][HEIGHT];
	GamePiece m_allPieces[WIDTH][HEIGHT];

	GamePiece* m_clickedPiece = nullptr;
	GamePiece* m_targetPiece = nullptr;

	GamePiece* m_clickedBomb = nullptr;
	GamePiece* m_targetBomb = nullptr;

	bool m_inputEnabled = true;

	Node *m_match3Scene;

	void Init(Node *match3Scene);
	void SetupTiles();
	void ManualSetup();
	GamePiece* MakeBomb(BombType type, int x, int y);
	void FillBoard(int falseYOffset = 0, float moveTime = 0.1f, bool randomIfMatch = false);
	GamePiece FillRandomPieceAt(int x, int y, int falseYOffset = 0, float moveTime = 0.1f);
	void ReplaceRandom(list<GamePiece> gamePieces, int falseYOffset = 0, float moveTime = 0.1f);

	void ClickTile(GamePiece* tile);
	void ReleaseTile(GamePiece* tile);
	void SwitchTile(GamePiece* clickedTile, GamePiece* targetTile);

	list<GamePiece> FindVertical(int startX, int startY, int minlength = 3);
	list<GamePiece> FindHorizontal(int startX, int startY, int minlength = 3);
	list<GamePiece> FindMatches(int startX, int startY, Vec2 searchDirection, int minLength = 3);
	list<GamePiece> FindMatchesAt(int x, int y, int minLength = 3);
	list<GamePiece> FindMatchesAt(list<GamePiece> gamePieces, int minLength = 3);
	list<GamePiece> FindAllMatches();
	list<GamePiece> FindAllMatchValue(MatchType mValue);

	void ClearPieceAt(int x, int y);
	void ClearPieceAt(list<GamePiece> gamePieces);
	void ClearRefillBoard(list<GamePiece> gamePieces);
	void RefillRoutine();
	void ClearCollapseRoutine(list<GamePiece> gamePieces);

	list<GamePiece> CollapseColumn(int column, float collapseTime = 0.5f);
	list<GamePiece> CollapseColumn(list<GamePiece> gamePieces, float collapseTime = 0.5f);
	list<int> GetColumns(list<GamePiece> gamePieces);
	list<GamePiece> GetRowPieces(int row);
	list<GamePiece> GetColPieces(int col);
	list<GamePiece> GetAdjPieces(int x, int y, int offset = 1);
	list<GamePiece> GetBombedPieces(list<GamePiece> gamePieces);
	GamePiece* DropBomb(int x, int y, Vec2 swapDirection, list<GamePiece> gamePieces);
	bool IsCornerMatch(list<GamePiece> gamePieces);	
	bool IsColorBomb(GamePiece piece);
	bool IsInbound(int x, int y);
	bool IsNextTo(GamePiece* start, GamePiece* end);
	void UnionList(list<GamePiece> &to, list<GamePiece> &from);
};


#include "BoardManager.h"
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <algorithm>
#include <list>
#include <iterator>
#include "ScoreManager.h"

BoardManager::~BoardManager()
{
	SafeDelete(m_clickedPiece);
	SafeDelete(m_targetPiece);
	SafeDelete(m_targetBomb);
	SafeDelete(m_clickedBomb);
	m_match3Scene->removeFromParentAndCleanup(true);
}

void BoardManager::Init(Node *match3Scene)
{
	m_match3Scene = match3Scene;
	SetupTiles();
	FillBoard(START_HEIGHT, START_MOVETIME, true);
	ManualSetup();
}

void BoardManager::SetupTiles()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (IsInbound(i, j))
			{
				m_allTiles[i][j].Init(m_match3Scene, i, j);
			}
		}
	}
}

void BoardManager::ManualSetup()
{
	//m_allPieces[0][0].ChangeColor(Red);
	//m_allPieces[0][1].ChangeColor(Red);
	//m_allPieces[1][2].ChangeColor(Red);
	//m_allPieces[2][2].ChangeColor(Red);
	//m_allPieces[0][3].ChangeColor(Red);

	//m_allPieces[0][0].ChangeColor(Red);
	//m_allPieces[0][1].ChangeColor(Red);
	//m_allPieces[1][2].ChangeColor(Red);
	//m_allPieces[0][3].ChangeColor(Red);
	//m_allPieces[0][4].ChangeColor(Red);

	//m_allPieces[0][5].ChangeColor(Yellow);
	//m_allPieces[0][6].ChangeColor(Yellow);
	//m_allPieces[1][7].ChangeColor(Yellow);
	//m_allPieces[0][8].ChangeColor(Yellow);
	//m_allPieces[0][9].ChangeColor(Yellow);
}

GamePiece* BoardManager::MakeBomb(BombType type, int x, int y)
{
	if (IsInbound(x, y))
	{
		GamePiece* bomb = &m_allPieces[x][y];
		m_allPieces[x][y].SwitchBomb(type);
		return bomb;
	}
	return nullptr;
}

void BoardManager::FillBoard(int falseYOffset, float moveTime, bool randomIfMatch)
{
	list<GamePiece> addedPieces;

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (m_allPieces[i][j].isEmpty())
			{
				if (randomIfMatch)
				{
					addedPieces.push_back(FillRandomPieceAt(i, j, falseYOffset, moveTime));
				}
				else
				{
					addedPieces.push_back(FillRandomPieceAt(i, j, falseYOffset, moveTime * TIME_MODIFIER(j)));
				}
			}
		}
	}
	if (randomIfMatch)
	{
		int maxIter = 10;
		int iter = 1;
		bool isFilled = false;

		while (!isFilled)
		{
			list<GamePiece> matches = FindAllMatches();

			if (matches.empty())
			{
				isFilled = true;
				break;
			}
			else
			{
				list<GamePiece> result;

				matches.sort();
				addedPieces.sort();
				set_intersection(matches.begin(), matches.end(), addedPieces.begin(), addedPieces.end(), back_inserter(result));

				ReplaceRandom(result, falseYOffset, moveTime);
			}

			if (iter > maxIter)
			{
				isFilled = true;
				log("Warning, too many fill");
				ClearRefillBoard(matches);
			}
			iter++;
		}
	}
}

GamePiece BoardManager::FillRandomPieceAt(int x, int y, int falseYOffset, float moveTime)
{
	if (IsInbound(x, y))
	{
		m_allPieces[x][y].Init(x, y, (MatchType)random(1, NUMBER_OF_COLOR), falseYOffset, moveTime);
	}
	return m_allPieces[x][y];
}

void BoardManager::ReplaceRandom(list<GamePiece> gamePieces, int falseYOffset, float moveTime)
{
	for each(GamePiece piece in gamePieces)
	{
		ClearPieceAt(piece.xIndex, piece.yIndex);
		FillRandomPieceAt(piece.xIndex, piece.yIndex, falseYOffset, moveTime);
	}
}

void BoardManager::ClickTile(GamePiece* tile)
{
	if (m_clickedPiece == nullptr &&
		m_inputEnabled)
	{
		m_clickedPiece = tile;
		m_clickedPiece->Hightlight();
	}
}

void BoardManager::ReleaseTile(GamePiece* tile)
{
	if (m_clickedPiece != nullptr &&
		IsNextTo(m_clickedPiece, tile) && m_inputEnabled)
	{
		m_targetPiece = tile;
	}
	else
	{
		if (m_clickedPiece != nullptr)
		{
			m_clickedPiece->Hightlight(false);
		}
		m_clickedPiece = nullptr;
		m_targetPiece = nullptr;
		return;
	}

	if (m_clickedPiece != nullptr
		&& m_targetPiece != nullptr
		&& m_inputEnabled)
	{
		m_inputEnabled = false;
		SwitchTile(m_clickedPiece, m_targetPiece);
	}
}

void BoardManager::SwitchTile(GamePiece* clickedTile, GamePiece* targetTile)
{
	int cx = clickedTile->xIndex;
	int cy = clickedTile->yIndex;
	int tx = targetTile->xIndex;
	int ty = targetTile->yIndex;

	if (m_targetPiece != nullptr && m_clickedPiece != nullptr)
	{
		m_allPieces[cx][cy].Move(tx, ty, SWAPTIME);
		m_allPieces[tx][ty].Move(cx, cy, SWAPTIME);

		DelayTime *pause = DelayTime::create(SWAPTIME + 0.1f);

		CallFunc* action = CallFunc::create([&, cx, cy, tx, ty]()
		{
			GamePiece temp = m_allPieces[cx][cy];
			m_allPieces[cx][cy] = m_allPieces[tx][ty];
			m_allPieces[tx][ty] = temp;

			list<GamePiece> clickedMatches = FindMatchesAt(cx, cy);
			list<GamePiece> targetMatches = FindMatchesAt(tx, ty);
			list<GamePiece> colorMatches;

			if (IsColorBomb(m_allPieces[cx][cy]) && !IsColorBomb(m_allPieces[tx][ty]))
			{
				m_allPieces[cx][cy].matchType = m_allPieces[tx][ty].matchType;
				colorMatches = FindAllMatchValue(m_allPieces[cx][cy].matchType);
			}
			else if (!IsColorBomb(m_allPieces[cx][cy]) && IsColorBomb(m_allPieces[tx][ty]))
			{
				m_allPieces[tx][ty].matchType = m_allPieces[cx][cy].matchType;
				colorMatches = FindAllMatchValue(m_allPieces[tx][ty].matchType);
			}
			else if (IsColorBomb(m_allPieces[cx][cy]) && IsColorBomb(m_allPieces[tx][ty]))
			{
				for each(GamePiece piece in m_allPieces)
				{
					if (!piece.isEmpty())
					{
						colorMatches.push_back(piece);
					}
				}
				colorMatches.unique();
			}

			if (targetMatches.empty() && clickedMatches.empty()
				&& colorMatches.empty())
			{
				m_allPieces[cx][cy].Move(tx, ty, SWAPTIME);
				m_allPieces[tx][ty].Move(cx, cy, SWAPTIME);

				DelayTime *pause2 = DelayTime::create(SWAPTIME + 0.1f);
				CallFunc* action2 = CallFunc::create([&, cx, cy, tx, ty]()
				{
					GamePiece temp2 = BoardManager::getInstance()->m_allPieces[cx][cy];
					BoardManager::getInstance()->m_allPieces[cx][cy] = BoardManager::getInstance()->m_allPieces[tx][ty];
					BoardManager::getInstance()->m_allPieces[tx][ty] = temp2;
					BoardManager::getInstance()->m_inputEnabled = true;
				});

				m_match3Scene->runAction(Sequence::create(pause2, action2, nullptr));
			}
			else
			{

				m_allPieces[cx][cy].Init(cx, cy, m_allPieces[cx][cy].matchType);
				m_allPieces[tx][ty].Init(tx, ty, m_allPieces[tx][ty].matchType);
#if ENABLED_BOMB
				Vec2 swipeDirection(m_allPieces[tx][ty].xIndex - m_allPieces[cx][cy].xIndex, m_allPieces[tx][ty].yIndex - m_allPieces[cx][cy].yIndex);
				if (clickedMatches.size() >= 4)
				{
					m_clickedBomb = DropBomb(m_allPieces[cx][cy].xIndex, m_allPieces[cx][cy].yIndex, swipeDirection, clickedMatches);
				}
				if (targetMatches.size() >= 4)
				{
					m_targetBomb = DropBomb(m_allPieces[tx][ty].xIndex, m_allPieces[tx][ty].yIndex, swipeDirection, targetMatches);
				}

				if (m_clickedBomb != nullptr
					&& !m_clickedBomb->isEmpty()
					&& !m_allPieces[tx][ty].isEmpty())
				{
					if (!IsColorBomb(*m_clickedBomb))
					{
						m_clickedBomb->ChangeColor(m_allPieces[cx][cy].matchType);
					}
				}

				if (m_targetBomb != nullptr
					&& !m_targetBomb->isEmpty()
					&& !m_allPieces[cx][cy].isEmpty())
				{
					if (!IsColorBomb(*m_targetBomb))
					{
						m_targetBomb->ChangeColor(m_allPieces[tx][ty].matchType);
					}
				}
#endif
				UnionList(clickedMatches, targetMatches);
				UnionList(clickedMatches, colorMatches);

				ClearRefillBoard(clickedMatches);
			}
		});

		m_match3Scene->runAction(Sequence::create(pause, action, nullptr));
	}
}

list<GamePiece> BoardManager::FindVertical(int startX, int startY, int minlength)
{
	list<GamePiece> upwardMatches = FindMatches(startX, startY, Vec2(0, 1), 2);
	list<GamePiece> downwardMatches = FindMatches(startX, startY, Vec2(0, -1), 2);

	UnionList(upwardMatches, downwardMatches);

	if ((int)upwardMatches.size() >= minlength)
	{
		return upwardMatches;
	}
	else
	{
		upwardMatches.clear();
		return upwardMatches;
	}
}

list<GamePiece> BoardManager::FindHorizontal(int startX, int startY, int minlength)
{
	list<GamePiece> upwardMatches = FindMatches(startX, startY, Vec2(1, 0), 2);
	list<GamePiece> downwardMatches = FindMatches(startX, startY, Vec2(-1, 0), 2);

	UnionList(upwardMatches, downwardMatches);

	if ((int)upwardMatches.size() >= minlength)
	{
		return upwardMatches;
	}
	else
	{
		upwardMatches.clear();
		return upwardMatches;
	}
}

list<GamePiece> BoardManager::FindMatches(int startX, int startY, Vec2 searchDirection, int minLength)
{
	list<GamePiece> matches;
	GamePiece startPiece;

	if (IsInbound(startX, startY))
	{
		matches.push_back(m_allPieces[startX][startY]);
	}

	int nextX;
	int nextY;

	int maxValue = (WIDTH > HEIGHT) ? WIDTH : HEIGHT;
	for (int i = 1; i < maxValue - 1; i++)
	{
		nextX = startX + (int)clip(searchDirection.x, -1.0f, 1.0f) * i;
		nextY = startY + (int)clip(searchDirection.y, -1.0f, 1.0f) * i;

		if (!IsInbound(nextX, nextY))
		{
			break;
		}

		if (m_allPieces[nextX][nextY].matchType == m_allPieces[startX][startY].matchType
			&& m_allPieces[nextX][nextY].matchType != None)
		{
			matches.push_back(m_allPieces[nextX][nextY]);
		}
		else
		{
			break;
		}
	}

	//remove duplicate
	matches.unique();

	if ((int)matches.size() >= minLength)
	{
		return matches;
	}
	else
	{
		matches.clear();
		return matches;
	}
}

list<GamePiece> BoardManager::FindMatchesAt(int x, int y, int minLength)
{
	list<GamePiece> horMatches = FindHorizontal(x, y, 3);
	list<GamePiece> verMatches = FindVertical(x, y, 3);

	UnionList(horMatches, verMatches);
	return horMatches;
}

list<GamePiece> BoardManager::FindMatchesAt(list<GamePiece> gamePieces, int minLength)
{
	list<GamePiece> matches;
	for each (GamePiece piece in gamePieces)
	{
		matches.sort();
		matches.merge(FindMatchesAt(piece.xIndex, piece.yIndex, minLength));
	}
	matches.unique();
	return matches;
}

list<GamePiece> BoardManager::FindAllMatches()
{
	list<GamePiece> combineMatches;

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			list<GamePiece> matches = FindMatchesAt(i, j);
			combineMatches.sort();
			combineMatches.merge(matches);
		}
	}
	combineMatches.unique();
	return combineMatches;
}

list<GamePiece> BoardManager::FindAllMatchValue(MatchType mValue)
{
	list<GamePiece> foundPieces;

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (!m_allPieces[i][j].isEmpty())
			{
				if (m_allPieces[i][j].matchType == mValue)
				{
					foundPieces.push_back(m_allPieces[i][j]);
				}
			}
		}
	}
	foundPieces.sort();
	return foundPieces;
}

void BoardManager::ClearPieceAt(int x, int y)
{
	m_allPieces[x][y].Clear();
	m_allPieces[x][y].ClearBomb();
}

void BoardManager::ClearPieceAt(list<GamePiece> gamePieces)
{
	gamePieces.unique();
	int score = 0;
	for each(GamePiece piece in gamePieces)
	{
		if (!piece.isEmpty())
		{
			ClearPieceAt(piece.xIndex, piece.yIndex);
			if (piece.bombType == NotBomb)
			{
				score += SCORE_NORMAL;
			}
			else
			{
				score += SCORE_BOMB_BONUS;
			}
		}
	}
	if (gamePieces.size() >= 5)
	{
		score += (gamePieces.size() - 5) * SCORE_OVER_BONUS ;
	}

	ScoreManager::getInstance()->AddScore(score);
}

void BoardManager::ClearRefillBoard(list<GamePiece> gamePieces)
{
	m_inputEnabled = false;

	list<GamePiece> matches = gamePieces;
	ClearCollapseRoutine(matches);
}

void BoardManager::RefillRoutine()
{
	FillBoard(START_HEIGHT, START_MOVETIME - 0.2f);
	list<GamePiece> matches = FindAllMatches();
	if (!matches.empty())
	{
		DelayTime *pause = DelayTime::create(0.75f);
		CallFunc* action = CallFunc::create([&, matches]()
		{
			ClearCollapseRoutine(matches);
		});
		m_match3Scene->runAction(Sequence::create(pause, action, nullptr));
	}
	else
	{
		DelayTime *pause = DelayTime::create(1.0f);
		CallFunc* action = CallFunc::create([&]()
		{
			//ReCheckMap();
			if (BoardManager::getInstance()->m_clickedBomb != nullptr)
			{
				BoardManager::getInstance()->m_clickedBomb = nullptr;
			}

			if (BoardManager::getInstance()->m_targetBomb != nullptr)
			{
				BoardManager::getInstance()->m_targetBomb = nullptr;
			}

			if (BoardManager::getInstance()->m_targetPiece != nullptr)
			{
				BoardManager::getInstance()->m_targetPiece = nullptr;
			}

			if (BoardManager::getInstance()->m_clickedPiece != nullptr)
			{
				BoardManager::getInstance()->m_clickedPiece = nullptr;
			}
			BoardManager::getInstance()->m_inputEnabled = true;
		});
		m_match3Scene->runAction(Sequence::create(pause, action, nullptr));
	}
}

void BoardManager::ClearCollapseRoutine(list<GamePiece> gamePieces)
{

	list<GamePiece> movingPieces;
	list<GamePiece> matches;
	if (m_clickedBomb != nullptr)
	{
		gamePieces.remove(*m_clickedBomb);
		m_clickedBomb = nullptr;
	}
	if (m_targetBomb != nullptr)
	{
		gamePieces.remove(*m_targetBomb);
		m_targetBomb = nullptr;
	}
	list<GamePiece> bombedPieces = GetBombedPieces(gamePieces);
	UnionList(gamePieces, bombedPieces);

	ClearPieceAt(gamePieces);
#if	COLLAPSE_ENABLED
	movingPieces = CollapseColumn(gamePieces, 0.5f);
#endif
	matches = FindMatchesAt(movingPieces);

	if (matches.empty())
	{
		DelayTime *pause2 = DelayTime::create(0.6f);
		CallFunc* action2 = CallFunc::create([&, matches]()
		{
			RefillRoutine();
		});
		m_match3Scene->runAction(Sequence::create(pause2, action2, nullptr));
		return;
	}
	else
	{
		DelayTime *pause2 = DelayTime::create(0.6f);
		CallFunc* action2 = CallFunc::create([&, matches]()
		{
			//m_scoreMulti++;
			ClearCollapseRoutine(matches);
		});
		m_match3Scene->runAction(Sequence::create(pause2, action2, nullptr));
	}
}

list<GamePiece> BoardManager::CollapseColumn(int column, float collapseTime)
{
	list<GamePiece> movingPieces;

	for (int i = 0; i < (HEIGHT - 1); i++)
	{
		if (m_allPieces[column][i].isEmpty())
		{
			for (int j = i + 1; j < HEIGHT; j++)
			{
				if (!m_allPieces[column][j].isEmpty())
				{
					m_allPieces[column][i].Init(column, j, m_allPieces[column][j].matchType);
					if (m_allPieces[column][j].bombType != NotBomb)
					{
						m_allPieces[column][i].SwitchBomb(m_allPieces[column][j].bombType);
					}
					m_allPieces[column][i].SetCoord(column, i);	//need to set x,y right away for calculation later
					m_allPieces[column][i].Move(column, i, collapseTime * TIME_MODIFIER(j));

					movingPieces.push_back(m_allPieces[column][i]);

					m_allPieces[column][j].Clear();
					m_allPieces[column][j].ClearBomb();
					break;
				}
			}
		}
	}
	movingPieces.unique();
	return movingPieces;
}

list<GamePiece> BoardManager::CollapseColumn(list<GamePiece> gamePieces, float collapseTime)
{
	list<GamePiece> movingPieces;

	list<int> columns = GetColumns(gamePieces);

	for each(int columm in columns)
	{
		UnionList(movingPieces, CollapseColumn(columm, collapseTime));
	}

	return movingPieces;
}

list<int> BoardManager::GetColumns(list<GamePiece> gamePieces)
{
	list<int> column;
	for each(GamePiece piece in gamePieces)
	{
		column.push_back(piece.xIndex);
	}
	column.unique();
	return column;
}

list<GamePiece> BoardManager::GetRowPieces(int row)
{
	list<GamePiece> gamePieces;

	for (int i = 0; i < WIDTH; i++)
	{
		if (!m_allPieces[i][row].isEmpty())
		{
			gamePieces.push_back(m_allPieces[i][row]);
		}
	}

	return gamePieces;
}

list<GamePiece> BoardManager::GetColPieces(int col)
{
	list<GamePiece> gamePieces;

	for (int i = 0; i < HEIGHT; i++)
	{
		if (!m_allPieces[col][i].isEmpty())
		{
			gamePieces.push_back(m_allPieces[col][i]);
		}
	}

	return gamePieces;
}

list<GamePiece> BoardManager::GetAdjPieces(int x, int y, int offset)
{
	list<GamePiece> gamePieces;

	for (int i = x - offset; i <= x + offset; i++)
	{
		for (int j = y - offset; j <= y + offset; j++)
		{
			if (IsInbound(i, j) && !m_allPieces[i][j].isEmpty())
			{
				gamePieces.push_back(m_allPieces[i][j]);
			}
		}
	}
	return gamePieces;
}

list<GamePiece> BoardManager::GetBombedPieces(list<GamePiece> gamePieces)
{
	list<GamePiece> allPiecesToClear;

	for each(GamePiece piece in gamePieces)
	{
		if (!piece.isEmpty())
		{
			list<GamePiece> piecesToClear;
			switch (piece.bombType)
			{
			case NotBomb:
				break;
			case Column:
				piecesToClear = GetColPieces(piece.xIndex);
				break;
			case Row:
				piecesToClear = GetRowPieces(piece.yIndex);
				break;
			case Adjacent:
				piecesToClear = GetAdjPieces(piece.xIndex, piece.yIndex);
				break;
			case Color:
				piecesToClear = FindAllMatchValue((MatchType)random(1, NUMBER_OF_COLOR));
				break;
			default:
				break;
			}
			UnionList(allPiecesToClear, piecesToClear);
		}
	}
	return allPiecesToClear;
}

GamePiece * BoardManager::DropBomb(int x, int y, Vec2 swapDirection, list<GamePiece> gamePieces)
{
	GamePiece * bomb = nullptr;

	if (gamePieces.size() >= 4)
	{
		if (IsCornerMatch(gamePieces))
		{
			bomb = MakeBomb(Adjacent, x, y);
		}
		else
		{
			if (gamePieces.size() >= 5)
			{
				bomb = MakeBomb(Color, x, y);
			}
			else if (swapDirection.x != 0)
			{
				bomb = MakeBomb(Row, x, y);
			}
			else
			{
				bomb = MakeBomb(Column, x, y);
			}
		}
	}
	return bomb;
}

bool BoardManager::IsCornerMatch(list<GamePiece> gamePieces)
{
	bool vertical = false;
	bool horizontal = false;
	int xStart = -1;
	int yStart = -1;

	for each(GamePiece piece in gamePieces)
	{
		if (!piece.isEmpty())
		{
			if (xStart == -1 || yStart == -1)
			{
				xStart = piece.xIndex;
				yStart = piece.yIndex;
				continue;
			}

			if (piece.xIndex != xStart)
			{
				horizontal = true;
			}

			if (piece.yIndex != yStart)
			{
				vertical = true;
			}
		}
	}
	return (horizontal && vertical);
}

bool BoardManager::IsColorBomb(GamePiece piece)
{
	if (!piece.isEmpty())
	{
		return (piece.bombType == Color);
	}

	return false;
}


bool BoardManager::IsInbound(int x, int y)
{
	return (x >= 0 && x < WIDTH
		&& y >= 0 && y <= HEIGHT);
}

bool BoardManager::IsNextTo(GamePiece* start, GamePiece* end)
{
	if (start != nullptr && end != nullptr)
	{
		if (abs(start->xIndex - end->xIndex) == 1 && start->yIndex == end->yIndex) return true;
		if (abs(start->yIndex - end->yIndex) == 1 && start->xIndex == end->xIndex) return true;
	}
	return false;
}

void BoardManager::UnionList(list<GamePiece>& to, list<GamePiece> &from)
{
	from.sort();
	to.sort();
	to.merge(from);
	to.unique();
}

//void BoardManager::ReCheckMap()
//{
//	for (int i = 0; i < WIDTH; i++)
//	{
//		for (int j = 0; j < HEIGHT; j++)
//		{
//			if (m_allPieces[i][j].xIndex != i)
//			{
//				m_allPieces[i][j].xIndex = i;
//			}
//			if (m_allPieces[i][j].yIndex != j)
//			{
//				m_allPieces[i][j].yIndex = j;
//			}
//		}
//	}
//}

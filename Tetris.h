#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <sstream>
#define GRIDSIZE 35
#define DALAYVALUE 0.3
#define STAGE_WIDTH 10
#define STAGE_HEIGHT 20
#define P1_STAGE_CORNER_X 156
#define P1_STAGE_CORNER_Y 174
#define P2_STAGE_CORNER_X 844
#define P2_STAGE_CORNER_Y 174
#define P1_NEXT_CORNER_X 587
#define P1_NEXT_CORNER_Y 125
#define P2_NEXT_CORNER_X 702
#define P2_NEXT_CORNER_Y 125
#define HOLD_CORNER_X 660
#define HOLD_CORNER_Y 275

typedef enum PLAYROLE {
	roleNONE, //空
	rolePLAYER1, //玩家 1
	rolePLAYER2, //玩家 2
};
typedef enum gridShape {
	shapeI,//I
	shapeS,//S
	shapeZ,//Z
	shapeT,//T
	shapeL,//L
	shapeJ,//J
	shapeO,//O
};
using namespace sf;

class Tetris
{
public:
	Tetris();
	~Tetris();
	Vector2i mCornPoint, nextSquareCornPoint, holdSquareCornPoint;//游戏区域位置
	int role;

	int gridSize;//块大小（18）
	int imgBGno, imgSkinNo;
	Texture* tTiles;
	Texture tBackground, tButtons, tNum, tTimer, tCounter, tGameOver;//创建纹理对象
	Sprite sBackground, sTiles, sButtons, sNum, sTimer, sCounter, sGameOver;//创建精灵对象
	

	int Field[STAGE_HEIGHT][STAGE_WIDTH] = { 0 };
	Vector2i currentSquare[4], nextSquare[4], tempSquare[4], shadowSquare[4];
	static Vector2i holdSquare[4];
	int Figures[7][4] =
	{
		3,5,1,7, // I
        4,5,2,7, // S
        4,5,3,6, // Z
        5,3,4,7, // T
        5,3,2,7, // L
        5,7,3,6, // J
        2,3,4,5  // O
	};
	int dx;

	int colorNum, nextcolorNum, tempcolorNum;
	int currentShapeNum, nextShapeNum, tempShapeNum;
	static int holdcolorNum, holdShapeNum;

	int b7array[7] = { 0 }, b7Int;
	float timer, delay;

	int score;

	bool rotate, hold, hardDrop, newShapeFlag, animationFlag;
	bool gameOver;
	int animationRow[4];
	float animationCtrlValue;
	sf::RenderWindow * window;

	void Initial(Texture *tex);
	void Input(sf::Event event);
	void Logic();
	void Draw(sf::RenderWindow* Window);
	void yMove();
	int Bag7();
	bool hitTest();
	void holdFunc();
	void xMove();
	void rotateFunc();
	void checkLine();
	void slowLoading();
	void hardDropFunc();
	void shadow();
	void traditionLogic();
	void clearLine();
	void newShapeFunc();
	void animationFunc(int i);
	void isWin();
};

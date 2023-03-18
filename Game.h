﻿#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <sstream>
#include "Tetris.h"
#define B_START_CORNER_X 621
#define B_START_CORNER_Y 763
#define B_HOLD_CORNER_X 621
#define B_HOLD_CORNER_Y 822
#define B_LEFT_CORNER_X 70
#define B_LEFT_CORNER_Y 460
#define B_RIGHT_CORNER_X 1295
#define B_RIGHT_CORNER_Y 460
#define P1_SCORE_CORNER_X 366
#define P1_SCORE_CORNER_Y 110
#define P2_SCORE_CORNER_X 1195
#define P2_SCORE_CORNER_Y 110
#define INFO_CORNER_X 570
#define INFO_CORNER_Y 475

using namespace sf;

typedef enum ButtonState {
	Continue_Dark, // 继续暗
	Continue_Light, // 继续亮
	Hold_Dark, // 暂停暗
	Hold_Light, // 暂停亮
	Close_Dark, // 结束暗
	Close_Light, // 结束亮
	Start_Dark, // 开始暗
	Start_Light, // 开始亮
	
};

class Game
{
public:
	Game();
	~Game();
	sf::RenderWindow window;
	Tetris player1, player2;
	bool gameOver, gameQuit;
	Clock clock;
	int Window_width, Window_height, stageWidth, stageHeight;
	bool isGameBegin,isGameHold;//------->游戏是否开始
	int isGameOverState;//------->游戏结束的状态
	Vector2i mCornPoint;//游戏区域位置
	int gridSize;//块大小（15）
	int imgSetNo;
	Texture tBackground, tTiles, tButtons, tSwitcher,tFrame, tCover, tScore, tGameOver; //创建纹理对象
	Sprite sBackground, sTiles, sButtons, sSwitcher,sFrame,sCover, sScore, sGameOver; //创建精灵对象
	sf::IntRect ButtonRectStart, ButtonRectHold, ButtonRectLeft, ButtonRectRight;
	int ButtonState_Start, ButtonState_Hold;
	SoundBuffer sbWin, sbBoom;
	Sound soundWin, soundBoom;
	Music bkMusic;
	sf::Clock gameClock, mouseClickTimer;
	Font font;
	Text text;

	void gameInitial();
	void LoadMediaData();

	void gameInput();
	void gameLogic();
	void gameDraw();
	void gameRun();
	
	void DrawButton();
	void DrawResults();
	void TextOut();
};

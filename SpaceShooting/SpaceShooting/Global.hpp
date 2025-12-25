//Global.hpp
//複数のソースで使用したい定義などをまとめたヘッダーファイル

#pragma once

//################## ヘッダファイル読み込み ##################
#include "DxLib.h"
#include "Mouse.hpp"
//#include "Font.hpp"
#include <vector>
#include <string>

//################## マクロ定義 ######################
#define GAME_LEFT	  0		//画面の横の始点
#define GAME_TOP	  0		//画面の縦の始点
#define GAME_WIDTH	800		//画面の横の大きさ
#define GAME_HEIGHT	600		//画面の縦の大きさ
#define GAME_FPS_SPEED					   60

//色関係
#define COLOR_RED	GetColor(255,0,0)		//赤色
#define COLOR_GREEN	GetColor(0,255,0)		//緑色
#define COLOR_BLUE	GetColor(0,0,255)		//青色
#define COLOR_WHITE GetColor(255,255,255)	//白色
#define COLOR_BLACK GetColor(0,0,0)			//黒色
#define COLOR_GRAY GetColor(128,128,128)	//灰色

//****************** その他 ***********************
#define INIT_VALUE		0	//初期値
#define FADE_MAX_CNT	60	//フェード処理のカウント最大値
#define TOUKA_MAX_VALUE	255	//透過の最大値

//##################### マクロ定義 #####################

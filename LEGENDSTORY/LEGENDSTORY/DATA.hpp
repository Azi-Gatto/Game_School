//DATA.hpp
//データクラス
//テキストファイルの文字コードをANSIにして保存する

#pragma once

//############## ヘッダファイル読み込み #################
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>
#include "PLAYER.hpp"
#include "ENEMY.hpp"
#include "ITEM.hpp"
#include "MSG.hpp"


//############## マクロ定義：ファイル名、パス ###################
#define ENEMY_DATA_DIR	R"(.\MY_DATA\Enemy\)"	//敵のデータのファイル名
#define MSG_DATA_DIR	R"(.\MY_DATA\Msg\)"		//メッセージのデータのファイル名
#define MAPPOS_DATA_DIR R"(.\MY_DATA\MapPos)"	//マップ位置のデータのファイル名
#define SAVE_DATA_DIR	R"(C:\LEGENDSTORY_DATA)"//セーブデータの保存ディレクトリ名

#define ENEMY_DATA_NAME		R"(Enemy_Data.csv)"	//敵のデータの名前
#define MSG_DATA_NAME		R"(Msg_Data.txt)"	//メッセージデータの名前
#define MAPPOS_DATA_NAME	R"(\MapPos_Data.csv)"//マップ位置のデータの名前
#define MAPPOS_INITDATA_NAME	R"(\MapPos_DataInit.csv)"	//マップ位置のデータの名前（初期）

//############## マクロ定義：エラーメッセージ ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//エラータイトル
#define DATA_ERROR_MSG		"データが読み込めませんでした"		//エラーメッセージ

//############## クラス定義 #####################
class DATA
{
private:

public:

	DATA();		//コンストラクタ

	~DATA();								//デストラクタ

	bool LoadEnemy(ENEMY *[],const char *, const char *);		//読み込み（敵データ）
	bool LoadMsg(MESSAGE *, const char *, const char *);		//読み込み（メッセージデータ）
	bool LoadNowMap(int *, int *, const char *, const char *);	//読み込み（現在のマップ位置）
	bool SaveMap(int, int[],const char *,const char *);			//現在のマップ位置をセーブ

};

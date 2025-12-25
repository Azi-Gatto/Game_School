//PLAYER.hpp
//プレイヤーを管理するクラス

#pragma once

//############## ヘッダファイル読み込み ####################
#include "DxLib.h"
#include "CHARACTOR.hpp"

//############## マクロ定義 #######################
#define IMG_DIR_PLAYER		R"(.\MY_IMG\Player)"		//プレイヤー関係の画像ディレクトリ

#define IMG_NAME_PLAYER		R"(\Player.png)"			//プレイヤーの画像の名前
#define IMG_NAME_PLAYER_ACT	R"(\Player_2.png)"			//アクション後のプレイヤーの画像の名前

#define PLAYER_START_X		50		//プレイヤーの描画開始X位置
#define PLAYER_START_Y		250		//プレイヤーの描画開始Y位置
#define PLAYER_AFTER_X		500		//プレイヤーの描画X位置（アクション後）
#define PLAYER_AFTER_Y		250		//プレイヤーの描画Y位置（アクション後）

//############### 列挙型 ####################
enum PLAYER_IMAGE
{
	PLAYER_IMG_NORMAL,		//通常時の画像
	PLAYER_IMG_ACT			//アクション後の画像
};

enum PLAYER_RESULT
{
	RESULT_WIN,			//プレイヤーが勝利
	RESULT_LOSE,		//プレイヤーが敗北
	RESULT_DRAW,		//引き分け
	RESULT_OTETUKI,		//お手付き
	RESULT_NONE = -1	//初期値
};

//############## クラス定義 #######################
class PLAYER : public CHARACTOR		//キャラクタークラスを継承
{

private:

	int WinNum;		//勝ち数
	double PushTime;//キーボードを押すまでにかかった時間
	int Result;		//結果

public:

	PLAYER(const char *,const char *);		//コンストラクタ
	~PLAYER();								//デストラクタ

	void IncreaseWinNum();		//勝ち数を増やす
	int GetWinNum();			//勝ち数を取得
	void ResetWinNum();			//勝ち数をリセット

	void SetPushTime(double);	//押すまでにかかった時間を設定
	double GetPushTime();		//押すまでにかかった時間を取得

	void SetResult(int);		//結果を設定
	int GetResult();			//結果を取得

};

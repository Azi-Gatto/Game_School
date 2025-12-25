//PLAYER.cpp
//プレイヤーを管理するクラス

//############## ヘッダファイル読み込み ##################
#include "PLAYER.hpp"

//############## クラス定義 #####################

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
PLAYER::PLAYER(const char *dir,const char *name)
{

	this->SetImage(dir, name);	//画像を生成

	//メンバー変数の初期化
	this->WinNum = 0;					//勝利数初期化
	this->PushTime = 0.0;				//押すのにかかった時間初期化
	this->Result = (int)RESULT_NONE;	//勝利結果初期化

	return;
}

//デストラクタ
PLAYER::~PLAYER()
{
	return;
}

//勝ち数を増やす
void PLAYER::IncreaseWinNum()
{
	++this->WinNum;
	return;
}

//勝ち数を取得
//戻り値：int：現在の勝ち数
int PLAYER::GetWinNum()
{
	return this->WinNum;
}

//勝ち数をリセット
void PLAYER::ResetWinNum()
{
	this->WinNum = 0;	//勝ち数をリセット
	return;
}

//押すまでの時間を設定
void PLAYER::SetPushTime(double time)
{
	//時間は、ミリ秒で指定されるため、秒数に変換して設定する
	this->PushTime = time/1000;
	return;
}

//押すまでの時間を取得
//戻り値：double：押すまでの時間
double PLAYER::GetPushTime()
{
	return this->PushTime;
}

//勝利結果設定
void PLAYER::SetResult(int result)
{
	this->Result = result;
	return;
}

//勝利結果取得
int PLAYER::GetResult()
{
	return this->Result;
}

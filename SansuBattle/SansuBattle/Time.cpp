//Time.cpp
//時間を管理するクラス

//################## ヘッダファイル読み込み ################
#include "Time.hpp"

//################## クラス定義 ##################

//コンストラクタ
Time::Time()
{
	//メンバー変数初期化
	StartTime = 0;		//計測開始時間初期化
	ElapsedTime = 0;	//経過時間初期化
	LimitTime = 0;		//制限時間初期化
	LimitInit = 0;		//制限時間初期値
	NowLimitTime = 0;	//残りの制限時間初期化
}

//コンストラクタ（制限時間の設定付き）
//引数：int：制限時間
Time::Time(int limit)
{
	//メンバー変数初期化
	StartTime = 0;		//計測開始時間初期化
	ElapsedTime = 0;	//経過時間初期化
	NowLimitTime = 0;	//残りの制限時間初期化
	LimitTime = limit;	//制限時間を設定
	LimitInit = LimitTime;	//制限時間の初期値を設定
}

//デストラクタ
Time::~Time() {}

//計測開始
void Time::SetTime()
{
	//ミリ秒単位で取得するため、1/1000倍して、秒単位に変換する
	StartTime = GetNowCount() / 1000;	//計測開始時間設定
	LimitTime = LimitInit;				//制限時間を初期値にする
}

//経過時間更新
void Time::UpdateElpasedTime()
{
	//ミリ秒単位で取得するため、1/1000倍して、秒単位に変換する
	ElapsedTime = (GetNowCount() / 1000) - StartTime;	//経過時間を更新
}

//制限時間更新
void Time::UpdateLimitTime()
{
	UpdateElpasedTime();	//経過時間を更新
	NowLimitTime = LimitTime - ElapsedTime;	//残りの制限時間を更新
}

//経過時間描画
//引数：int：描画X位置
//引数：int：描画Y位置
void Time::DrawElapsedTime(int x, int y)
{
	UpdateElpasedTime();	//経過時間を更新
	DrawFormatStringToHandle(x, y, COLOR_WHITE, Font::GetNowHandle(), "%d", ElapsedTime);	//経過時間を描画
}

//制限時間描画
//引数：int：描画X位置
//引数：int：描画Y位置
void Time::DrawLimitTime(int x, int y)
{
	UpdateLimitTime();	//残りの制限時間更新
	if (NowLimitTime <= CHENGE_TIME)	//基準時間より少なくなったら
	{
		//描画色赤
		DrawFormatStringToHandle(x, y, COLOR_RED, Font::GetNowHandle(), "%2d", NowLimitTime);	//制限時間を描画
	}
	else
	{
		DrawFormatStringToHandle(x, y, COLOR_GREEN, Font::GetNowHandle(), "%2d", NowLimitTime);	//制限時間を描画
	}
}

//経過時間取得
int Time::GetElapsedTime()
{
	return ElapsedTime;
}

//制限時間が過ぎたか取得
//戻り値:true 制限時間が過ぎている :false 制限時間が過ぎていない
bool Time::GetIsLimit()
{
	UpdateLimitTime();	//制限時間更新
	return NowLimitTime <= 0 ? true : false;
}

//残りの制限時間をマイナスする
//引数：int：減らす時間（秒）
void Time::MinusLimitTime(int value)
{
	LimitTime -= value;	//制限時間を減らす
}

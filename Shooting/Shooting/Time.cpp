//Time.cpp
//時間を管理するクラス

//################## ヘッダファイル読み込み ################
#include "Time.hpp"

//################## クラス定義 ##################

//コンストラクタ
Time::Time()
{
	//メンバー変数初期化
	StartTime = 0;		//計測開始時間
	ElapsedTime = 0;	//経過時間
	NowLimit = 0;		//残りの制限時間
	Limit = 0;			//制限時間
	LimitInit = 0;		//制限時間の初期値
}

//コンストラクタ（制限時間の設定付き）
//引数：int：制限時間
Time::Time(int limit)
{
	//メンバー変数初期化
	StartTime = 0;		//計測開始時間
	ElapsedTime = 0;	//経過時間
	NowLimit = limit;	//残りの制限時間
	Limit = limit;		//制限時間
	LimitInit = NowLimit;	//制限時間の初期値
}

//デストラクタ
Time::~Time() {}

//制限時間設定
void Time::SetLimit(int limit)
{
	NowLimit = limit;
	LimitInit = limit;
}

//計測開始
void Time::StartCount()
{
	//ミリ秒単位で取得するため、1/1000倍して、秒単位に変換する
	StartTime = GetNowCount() / 1000;	//計測開始時間設定
	ElapsedTime = (GetNowCount() / 1000) - StartTime;	//経過時間を設定
	Limit = LimitInit;	//制限時間初期化
	NowLimit = Limit;	//残りの制限時間設定
}

//更新
void Time::UpDate()
{
	//ミリ秒単位で取得するため、1/1000倍して、秒単位に変換する
	ElapsedTime = (GetNowCount() / 1000) - StartTime;	//経過時間を更新
	NowLimit = Limit - ElapsedTime;						//残りの時間を更新
}

//制限時間描画
//引数：int：描画X位置
//引数：int：描画Y位置
void Time::Draw(int x, int y)
{
	UpDate();	//更新
	DrawFormatStringToHandle(x, y, COLOR_BLACK, Font::GetNowHandle() ,"%d", NowLimit);	//制限時間を描画
}

//制限時間が過ぎたか取得
//戻り値:true 制限時間が過ぎている :false 制限時間が過ぎていない
bool Time::GetIsLimit()
{
	UpDate();	//更新
	return NowLimit <= 0 ? true : false;
}

//渡された値の分時間を加算する
//引数：int：加える時間（秒）
void Time::Add(int value)
{
	Limit += value;	//時間を加える
}

//Time.hpp
//時間を管理するクラス

#pragma once

//################## ヘッダファイル読み込み ################
#include "Global.hpp"

//################## マクロ定義 ###################
#define CHENGE_TIME 5	//描画色を切り替える基準時間
//################## クラス定義 ###################
class Time
{
private:

	int StartTime;						//計測開始時間
	int ElapsedTime;					//経過時間
	int LimitTime;						//制限時間
	int LimitInit;						//制限時間の初期値
	int NowLimitTime;					//残りの制限時間

public:

	Time();								//コンストラクタ
	Time(int);							//コンストラクタ（制限時間の設定付き）
	~Time();							//デストラクタ

	void SetTime();						//計測開始
	void UpdateElpasedTime();			//経過時間更新
	void UpdateLimitTime();				//制限時間更新
	void DrawElapsedTime(int, int);		//経過時間描画
	void DrawLimitTime(int, int);		//制限時間描画

	int GetElapsedTime();				//経過時間取得
	bool GetIsLimit();					//制限時間が過ぎたか

	void MinusLimitTime(int);			//残りの制限時間をマイナスする

};

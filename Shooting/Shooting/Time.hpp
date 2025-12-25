//Time.hpp
//時間を管理するクラス

#pragma once

//############## ヘッダファイル読み込み #############
#include "Global.hpp"

//############## マクロ定義 ##############

//############## クラス定義 ##############
class Time
{

private:

	int StartTime;						//計測開始時間
	int ElapsedTime;					//経過時間
	int NowLimit;						//残りの制限時間
	int Limit;							//制限時間
	int LimitInit;						//制限時間の初期値

public:

	Time();								//コンストラクタ
	Time(int);							//コンストラクタ（制限時間の設定付き）
	~Time();							//デストラクタ

	void SetLimit(int);					//制限時間設定
	void StartCount();					//計測開始
	void UpDate();						//更新
	void Draw(int, int);				//制限時間描画

	bool GetIsLimit();					//制限時間が過ぎたか

	void Add(int);						//渡された値の分時間を加算する

};


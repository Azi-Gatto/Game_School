/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* Fps.hpp     																					   */
/* Fps(Flame Per Second)クラス																	   */
/* 一つのインスタンスのみにする																	   */

#pragma once

//########## ヘッダーファイル読み込み ##########
#include "Global.hpp"

//########## クラスの定義 ##########
class Fps
{
private:
	int			value;					//FPS値
	double		drawValue;				//DrawするときのFPS値
	double		calcStartTime;			//0フレーム目の開始時刻
	double		calcEndTime;			//設定したフレームの終了時刻
	double		flameCount;				//フレームのカウント
	double		calcAverage; 			//FPSを計算するための平均サンプル数

	int			TotalFlameCnt;			//現在の総フレーム数

public:

	//コンストラクタ
	//引　数：int　：FPS値
	Fps(int);

	//指定したFPSになるように待つ
	void Wait(void);

	//画面更新の時刻を取得する
	void Update(void);

	//FPSの値を表示する
	//引　数：int　：値を表示するX位置
	//引　数：int　：値を表示するY位置
	void Draw(int, int);

	//FPS値を取得する
	int Getvalue(void);

	//総フレームを取得する
	int GetTotalFlameCnt(void);

	//デストラクタ
	virtual ~Fps();
};

//########## 外部オブジェクト ##########
extern Fps *fps;
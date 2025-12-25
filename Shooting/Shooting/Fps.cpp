/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* Fps.cpp     																					   */
/* Fps(Flame Per Second)クラス																	   */
/* 一つのインスタンスのみにする																	   */

//########## ヘッダーファイル読み込み ##########
#include "Fps.hpp"

//########## クラスの定義 ##########

//コンストラクタ
Fps::Fps(int fps_value)
{
	value = fps_value;
	drawValue = 0;
	calcStartTime = 0;
	flameCount = 0;
	calcAverage = (double)value;

	TotalFlameCnt = 0;

	return;
}

//指定したFPSになるように待つ
void Fps::Wait(void)
{
	//現在の時刻をミリ秒で取得
	double nowTime = GetTickCount();

	//1フレーム目から実際にかかった時間を計算
	double keikaTime = nowTime - calcStartTime;

	//ゼロ除算対策
	if (value > 0)
	{
		//待つべき時間 = フレーム数ごとにかかるべき時間 - 実際にかかった時間;
		int wait_tm = (flameCount * 1000 / value) - (keikaTime);

		//待つべき時間があった場合
		if (wait_tm > 0)
		{
			//ミリ秒分、処理を中断する
			Sleep(wait_tm);
		}
	}

	//総フレームをカウント
	TotalFlameCnt++;

	return;
}

//画面更新の時刻を取得する
void Fps::Update(void)
{
	//1フレーム目なら時刻を記憶
	if (flameCount == 0)
	{
		//Windowsが起動してから現在までの時刻をミリ秒で取得
		calcStartTime = GetTickCount();
	}

	//指定フレームの最後のフレームなら、平均を計算する
	if (flameCount == calcAverage)
	{
		//Windowsが起動してから現在までの時刻をミリ秒で取得
		calcEndTime = GetTickCount();

		//平均的なFPS値を計算
		drawValue = 1000.0f / ((calcEndTime - calcStartTime) / calcAverage);

		//次のFPS計算の準備
		calcStartTime = calcEndTime;

		//カウント初期化
		flameCount = 0;
	}

	//フレーム数カウントアップ
	flameCount++;

	return;
}

//FPSの値を表示する
void Fps::Draw(int drawX, int drawY)
{
	//文字列を描画
	DrawFormatString(drawX, drawY, GetColor(255, 255, 255), "FPS:%.1f", drawValue);
	return;
}

//FPS値を取得する
int Fps::Getvalue(void)
{
	return value;
}

//総フレームを取得する
int Fps::GetTotalFlameCnt(void)
{
	return TotalFlameCnt;
}

//デストラクタ
Fps::~Fps()
{
	return;
}
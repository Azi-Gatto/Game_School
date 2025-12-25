//Score.hpp
//スコアを管理するクラス

#pragma once

//############ ヘッダファイル読み込み #############
#include "Global.hpp"

//############ マクロ定義 #################
#define SCORE_DRAW_X	10	//スコア描画X位置
#define SCORE_DRAW_Y	10	//スコア描画Y位置

//############ クラス定義 #############
class Score
{
private:

	static int score;		//スコア

public:

	Score();		//コンストラクタ
	~Score();		//デストラクタ

	static int GetScore();			//スコア取得
	static void AddScore(int);		//スコア加算
	static void Draw();				//スコア描画
	static void Reset();			//リセット

};

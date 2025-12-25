//Score.cpp
//スコアを管理するクラス

//############ ヘッダファイル読み込み ############
#include "Score.hpp"

//############ クラス定義 ################

int Score::score = 0;	//スコア

//コンストラクタ
Score::Score(){}

//デストラクタ
Score::~Score(){}

//スコア取得
int Score::GetScore()
{
	return score;
}

//スコア加算
void Score::AddScore(int value)
{
	score += value;	//加算
}

//スコア描画
void Score::Draw()
{
	DrawFormatStringToHandle(SCORE_DRAW_X, SCORE_DRAW_Y, COLOR_BLACK, Font::GetNowHandle(), "%d", score);
}

//リセット
void Score::Reset()
{
	score = 0;
}

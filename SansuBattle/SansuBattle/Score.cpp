//Score.cpp
//スコアを管理するクラス

//############ ヘッダファイル読み込み ############
#include "Score.hpp"

//############ クラス定義 ################

int Score::score = 0;	//スコア
//スコアテーブル
vector<int> Score::ScoreTable = { SCORE_SUM_ANSER ,			//足し算の時のスコア
								  SCORE_DIFFERENCE_ANSER,	//引き算の時のスコア
								  SCORE_PRODUCT_ANSER,		//掛け算の時のスコア
								  SCORE_DEALER_ANSER,		//割り算の時のスコア
								  SCORE_SUM_DIF_ANSER,		//足し算、引き算の時のスコア
								  SCORE_PRO_DEA_ANSER,		//掛け算、割り算の時のスコア
								  SCORE_SUM_PRO_ANSER,		//+*の時のスコア
								  SCORE_SUM_DEA_ANSER,		//+/の時のスコア
								  SCORE_DIF_PRO_ANSER,		//-*の時のスコア
								  SCORE_SUM_DIF_PRO_ANSER,	//+-*の時のスコア
								  SCORE_SUM_DIF_DEA_ANSER,	//+-/の時のスコア
								  SCORE_ALL_ANSER };		//+-*/の時のスコア
//ボーナステーブル
vector<int> Score::LevBonus = { LEVEL_BONUS_EASY,			//簡単のときのボーナス
								LEVEL_BONUS_NORMAL,			//普通のときのボーナス
								LEVEL_BONUS_HARD };			//難しいのときのボーナス

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
void Score::AddScore(int mode, int lev, int time)
{

	//加算させるスコア量の設定
	int value = ScoreTable.at(mode);	//ゲームモード毎のスコアを取得

	const int time_excellent = 5;		//エクセレントの評価基準の時間(5秒以内)
	const int time_great = 15;			//グレートの評価基準の時間(15秒以内)

	if (time <= time_excellent)	//エクセレントの評価基準より短ければ
	{
		value *= TIME_BONUS_EXCELLENT;	//エクセレントのボーナスを加えて計算
	}
	else if (time <= time_great)//グレートの評価基準より短ければ
	{
		value *= TIME_BONUS_GREAT;		//グレートのボーナスを加えて計算
	}

	value *= LevBonus.at(lev);	//レベル毎のボーナスを乗算

	score += value;	//スコア加算

}

//スコア描画
void Score::Draw()
{

	int Strlen = strlen(std::to_string(score).c_str());														//文字列の長さを取得
	int Width = GetDrawStringWidthToHandle(std::to_string(score).c_str(), Strlen, Font::GetNowHandle());	//横幅取得

	DrawFormatStringToHandle((GAME_WIDTH / 2) - (Width / 2), GAME_TOP, COLOR_WHITE, Font::GetNowHandle(), "%d", score);		//スコア表示
}

//指定された領域内の中央に描画
void Score::DrawCenter(RECT rect)
{
	int Strlen = strlen(std::to_string(score).c_str());														//文字列の長さを取得
	int Width = GetDrawStringWidthToHandle(std::to_string(score).c_str(), Strlen, Font::GetNowHandle());	//横幅取得
	int Height = GetFontSizeToHandle(Font::GetNowHandle());	//高さ取得
	

	int rect_center_x = rect.left + ((rect.right - rect.left) / 2);	//領域の中央X位置を計算
	int rect_center_y = rect.top + ((rect.bottom - rect.top) / 2);	//領域の中央Y位置を計算
	int x = rect_center_x - (Width / 2);							//描画位置Xを計算
	int y = rect_center_y - (Height / 2);							//描画位置Yを計算

	DrawFormatStringToHandle(x, y, COLOR_WHITE, Font::GetNowHandle(), "%d", score);		//スコア表示
}

//リセット
void Score::Reset()
{
	score = 0;
}

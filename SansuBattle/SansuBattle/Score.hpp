//Score.hpp
//スコアを管理するクラス

#pragma once

//############ ヘッダファイル読み込み #############
#include "Global.hpp"

//############ マクロ定義 #################
#define TIME_BONUS_EXCELLENT	2		//回答時間がエクセレントの時のボーナス倍率
#define TIME_BONUS_GREAT		1.5		//回答時間がグレートの時のボーナス倍率
#define LEVEL_BONUS_EASY		1		//簡単レベルのボーナス倍率
#define LEVEL_BONUS_NORMAL		2		//普通レベルのボーナス倍率
#define LEVEL_BONUS_HARD		3		//難しいレベルのボーナス倍率

#define SCORE_SUM_ANSER			100		//足し算の回答をした時のスコア
#define SCORE_DIFFERENCE_ANSER	150		//引き算の回答をした時のスコア
#define SCORE_PRODUCT_ANSER		200		//掛け算の回答をした時のスコア
#define SCORE_DEALER_ANSER		250		//割り算の回答をした時のスコア
#define SCORE_SUM_DIF_ANSER		300		//足し算、引き算の回答をした時のスコア
#define SCORE_PRO_DEA_ANSER		350		//掛け算、割り算の回答をした時のスコア
#define SCORE_SUM_PRO_ANSER		400		//+*の回答をした時のスコア
#define SCORE_SUM_DEA_ANSER		450		//+/の回答をした時のスコア
#define SCORE_DIF_PRO_ANSER		500		//-*の回答をした時のスコア
#define SCORE_SUM_DIF_PRO_ANSER	550		//+-*の回答をした時のスコア
#define SCORE_SUM_DIF_DEA_ANSER	600		//+-/の回答をした時のスコア
#define SCORE_ALL_ANSER			650		//+-*/の回答をした時のスコア

//############ クラス定義 #############
class Score
{
private:

	static int score;		//スコア

	static vector<int> ScoreTable;	//ゲームモード毎のスコア
	static vector<int> LevBonus;	//ゲームレベル毎のボーナス

public:

	Score();		//コンストラクタ
	~Score();		//デストラクタ

	static int GetScore();				//スコア取得
	static void AddScore(int,int,int);	//スコア加算
	static void Draw();					//スコア描画
	static void DrawCenter(RECT);		//指定された領域内の中央に描画
	static void Reset();				//リセット

};

//GameMode.hpp
//各ゲームモードの基になるクラス

#pragma once

//############## ヘッダファイル読み込み #############
#include "Global.hpp"
#include <string>
#include "KeyDown.hpp"
#include "Image.hpp"

//############## マクロ定義 ###############
//問題関係
#define Q_IMG_DRAW_Y 490	//問題の画像（黒板）描画Y位置
#define Q_DRAW_Y 500		//問題の描画Y位置

#define Q_EASY_VALUE_MAX 9	//簡単モードの問題の最大値

#define Q_IMAGE_DIR		R"(.\MY_IMG\Question)"		//問題関係の画像のディレクトリ

#define	Q_IMAGE_KOKUBAN_NAME	R"(\kokuban.png)"	//黒板の画像の名前

//スコア関係
#define TIME_BONUS_EXCELLENT	2		//回答時間がエクセレントの時のボーナス倍率
#define TIME_BONUS_GREAT		1.5		//回答時間がグレートの時のボーナス倍率
#define LEVEL_BONUS_EASY		1		//簡単レベルのボーナス倍率
#define LEVEL_BONUS_NORMAL		2		//普通レベルのボーナス倍率
#define LEVEL_BONUS_HARD		3		//難しいレベルのボーナス倍率

//################# 列挙型 ###################
enum INPUT_NUM
{
	INPUT_NUM_0,		//入力値0
	INPUT_NUM_1,		//入力値1
	INPUT_NUM_2,		//入力値2
	INPUT_NUM_3,		//入力値3
	INPUT_NUM_4,		//入力値4
	INPUT_NUM_5,		//入力値5
	INPUT_NUM_6,		//入力値6
	INPUT_NUM_7,		//入力値7
	INPUT_NUM_8,		//入力値8
	INPUT_NUM_9,		//入力値9
	INPUT_ENTER = 100,	//決定キー
	INPUT_NOT_NUM = -1	//数値以外
};		//入力値の値

using std::string;

//############### クラス定義 #################
class GameMode
{
protected:

	//問題関係
	static Image* img_kokuban;		//黒板の画像
	string Q_Text;					//問題文
	int Anser;						//答え
	int InputNum;					//入力された数字
	bool IsCreate;					//問題を作成したか

	//スコア関係
	int Score;						//得点

private:

	int GetInputNum(KeyDown*);		//入力された数字を取得

public:

	GameMode();						//コンストラクタ
	~GameMode();					//デストラクタ

	//問題関係
	virtual void CreateQuestion(int) = 0;	//問題作成

	void DrawQuestion();			//問題を描画する
	void DrawInputNum();			//入力中の数字を描画する

	bool JudgAnser();				//正解か判定する

	bool CheckInputKey(KeyDown*);	//キー入力中か取得

	bool GetIsCreate();				//問題を作成したか取得

	void Reset();					//問題をリセット

	//スコア関係
	virtual void CalcScore(int, int) = 0;	//スコア計算処理
	void DrawNowScore();					//現在のスコア表示
	void ResetScore();						//スコアリセット

	int GetScore();							//スコア取得


};

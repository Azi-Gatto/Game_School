//Player.hpp
//プレイヤーを管理するクラス

#pragma once

//##################### ヘッダファイル読み込み #######################
#include "Charactor.hpp"
#include "KeyDown.hpp"

//##################### マクロ定義 #########################
#define IMG_DIR_PLAYER	R"(.\Image\Player)"		//プレイヤーの画像のディレクトリ

#define IMG_NAME_HP		R"(\hp.png)"				//HP画像の名前

#define PLAYER_HP_DRAW_Y		420	//HPの描画開始Y位置

#define INP_MAX_DIGIT		4		//入力される値の最大桁数

//##################### 列挙型 ##########################
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
	INPUT_BACK = 200,	//バックキー
	INPUT_MINUS = 300,	//マイナスキー
	INPUT_NOT_NUM = -1	//数値以外
};		//入力値の値

//##################### クラス定義 #########################
class Player : public Charactor		//キャラクタークラスを継承
{
private:

	int InputNum;				//入力された数字
	KeyDown* keydown;			//キー入力

	int GetInputKey();			//入力されたキーを取得

public:

	Player();	//コンストラクタ
	~Player();	//デストラクタ

	bool SetInit() override;	//初期設定

	void DrawInputNum();		//入力中の数字を描画する
	bool CheckInputKey();		//キー入力中か取得
	void InpReset();			//入力文字リセット
	int GetAns();				//入力された答えを取得

};

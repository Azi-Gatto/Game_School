//ENEMY.hpp
//敵を管理するクラス

#pragma once

//################ ヘッダファイル読み込み #################
#include "CHARACTOR.hpp"

//################ マクロ定義 ##################
#define IMG_DIR_ENEMY		R"(.\MY_IMG\Enemy)"		//敵関係の画像ディレクトリ

#define IMG_NAME_ENEMY		R"(\Enemy.png)"			//敵の画像の名前
#define IMG_NAME_ENEMY_ACT	R"(\Enemy_2.png)"		//アクション後の敵の画像の名前

#define ENEMY_START_X		600		//敵の描画開始X位置
#define ENEMY_START_Y		250		//敵の描画開始Y位置
#define ENEMY_AFTER_X		50		//敵の描画X位置（アクション後）
#define ENEMY_AFTER_Y		250		//敵の描画Y位置（アクション後）

#define ENEMY_SPD_MIN		0.5		//敵のはやさの最小値
#define ENEMY_SPD_INIT		1.5		//敵のはやさの初期値
#define ENEMY_SPD_UP_VALUE	0.1		//一回に早くなる値

//################ 列挙型 ################
enum ENEMY_IMAGE
{
	ENEMY_IMG_NORMAL,		//通常時の画像
	ENEMY_IMG_ACT			//アクション後の画像
};

//################ クラス定義 ##################
class ENEMY :public CHARACTOR	//キャラクタークラスを継承
{

private:

	double Speed;									//速度

public:

	ENEMY(const char *,const char *);		//コンストラクタ
	~ENEMY();								//デストラクタ

	double GetSpeed();	//速度を取得
	void SpeedUp();		//速度を早くする
	void SpeedReset();	//速度をリセットする

};

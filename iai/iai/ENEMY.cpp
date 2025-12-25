//ENEMY.cpp
//敵を管理するクラス

//############### ヘッダファイル読み込み #################
#include "ENEMY.hpp"

//############### クラス定義 ###################

//コントラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
ENEMY::ENEMY(const char *dir,const char *name)
{

	this->SetImage(dir, name);	//画像を生成

	//メンバー変数初期化
	this->Speed = ENEMY_SPD_INIT;		//はやさを初期化

	return;
}

//デストラクタ
ENEMY::~ENEMY()
{
	return;
}

//速度を取得
double ENEMY::GetSpeed()
{
	return this->Speed;
}

//速度を早くする
void ENEMY::SpeedUp()
{
	if (this->Speed > ENEMY_SPD_MIN)		//最高速度より遅ければ
	{
		this->Speed -= ENEMY_SPD_UP_VALUE;	//加速
	}
	return;
}

//速度をリセットする
void ENEMY::SpeedReset()
{
	this->Speed = ENEMY_SPD_INIT;	//速さを初期化
	return;
}

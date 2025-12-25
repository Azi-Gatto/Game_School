//Charactor.cpp
//キャラクタークラス

//################# ヘッダファイル読み込み #####################
#include "Charactor.hpp"

//################ クラス定義 ########################

//コンストラクタ
Charactor::Charactor()
{
	//メンバー変数初期化
	HP_X = 0;			//HP描画X位置
	HP_Y = 0;			//HP描画Y位置
	reverse = false;	//反転描画するか
	IsArive = true;		//生きているか初期化
	KillFlg = false;	//キルフラグ
	HP = HP_INIT_VALUE;	//HP初期化

	hp_img = new Image();	//画像のインスタンス生成

}

//デストラクタ
Charactor::~Charactor()
{
	delete hp_img;	//hp_img破棄
}

//初期化
void Charactor::Init()
{
	HP = HP_INIT_VALUE;	//HP初期化
	IsArive = true;		//生きている
	KillFlg = false;	//キルフラグリセット
}

//初期設定
bool Charactor::SetInit()
{
	if (!hp_img->GetIsLoad()) { return false; }	//読み込み失敗
	hp_img->SetInit();		//画像
}

//生きているか取得
bool Charactor::GetIsArive()
{
	return IsArive;
}

//ダメージを与える
void Charactor::SendDamege()
{
	--HP;	//ダメージを与える
	if (HP <= 0)	//HPが0以下になったら
	{
		HP = 0;	//HPは0
		IsArive = false;	//生きていない
	}
}

//キャラを殺す
void Charactor::Kill()
{
	KillFlg = true;
}

//HP取得
int Charactor::GetHp()
{
	return HP;
}

//描画
void Charactor::Draw()
{
	for (int i = 0; i < HP; ++i)
	{
		if (reverse)	//反転描画するとき
		{
			hp_img->Draw(HP_X - i * hp_img->GetWidth(), HP_Y);	//反転描画
		}
		else	//通常描画のとき
		{
			hp_img->Draw(HP_X + i * hp_img->GetWidth(), HP_Y);	//HP描画
		}
	}
}

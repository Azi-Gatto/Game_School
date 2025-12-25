//Toy.cpp
//的（プラスポイント）のクラス

//############## ヘッダファイル読み込み ################
#include "Toy.hpp"

//############## クラス定義 ###################

//コンストラクタ
//引数:Image* : 的の画像
//引数:Effect* :エフェクト
Toy::Toy(Image* img,Effect* effect)
{
	this->img = img;		//画像
	this->effect = effect;	//エフェクト
	time->SetLimit(GetRand(LIMIT_MAX - LIMIT_MIN) + LIMIT_MIN);	//制限時間設定
}

//デストラクタ
Toy::~Toy(){}

//クリックされた時の処理
void Toy::Event(Time* limit)
{
	effect->DrawCenter(rect);		//エフェクト描画
	if (effect->GetIsEffectEnd())	//エフェクト描画が終わったら
	{
		Score::AddScore(ScoreTable.at(Element));			//スコア加算
		effect->Reset();			//エフェクトリセット
		img->SetIsDraw(false);		//的非表示
		SetEventFlg(false);			//イベント終了
		time->StartCount();			//再計測
	}
}
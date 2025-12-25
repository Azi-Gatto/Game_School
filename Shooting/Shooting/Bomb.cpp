//Bomb.cpp
//爆弾（マイナスの的）のクラス

//########## ヘッダファイル読み込み ##############
#include "Bomb.hpp"

//########## クラス定義 ############

//コンストラクタ 
Bomb::Bomb(Image* img,Effect* effect)
{
	this->img = img;		//画像
	this->effect = effect;	//エフェクト
	time->SetLimit(GetRand(LIMIT_MAX - LIMIT_MIN) + LIMIT_MIN);	//制限時間設定
}

//デストラクタ
Bomb::~Bomb(){}

//クリックされた時の処理
void Bomb::Event(Time* limit)
{
	effect->DrawCenter(rect);			//エフェクト描画
	if (effect->GetIsEffectEnd())		//エフェクト描画が終わったら
	{
		Score::AddScore(ScoreTable.at(Element));			//スコア加算
		effect->Reset();				//エフェクトリセット
		img->SetIsDraw(false);			//的非表示
		limit->Add(BOMB_TIME_VALUE);	//時間を減らす
		SetEventFlg(false);				//イベント終了
	}
	time->StartCount();		//再計測
}

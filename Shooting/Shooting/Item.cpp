//Item.cpp
//アイテム（時間回復効果を持つ的）のクラス

//######## ヘッダファイル読み込み ############
#include "Item.hpp"

//########### クラス定義 ##############

//コンストラクタ
//引数:Image* : 的の画像
//引数:Effect* :エフェクト
Item::Item(Image* img, Effect* effect)
{
	this->img = img;		//画像
	this->effect = effect;	//エフェクト
	time->SetLimit(GetRand(LIMIT_MAX - LIMIT_MIN) + LIMIT_MIN);	//制限時間設定
}

//デストラクタ
Item::~Item() {}

//クリックされた時の処理
void Item::Event(Time* limit)
{
	effect->DrawCenter(rect);			//エフェクト描画
	if (effect->GetIsEffectEnd())		//エフェクト描画が終わったら
	{
		effect->Reset();				//エフェクトリセット
		img->SetIsDraw(false);			//的非表示
		limit->Add(ITEM_TIME_VALUE);	//時間を加算
		SetEventFlg(false);				//イベント終了
	}

	time->StartCount();		//再計測
}

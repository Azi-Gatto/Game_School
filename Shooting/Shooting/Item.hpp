//Item.hpp
//アイテム（時間回復効果を持つ的）のクラス

#pragma once

//########### ヘッダファイル読み込み ############
#include "Target.hpp"

//########### マクロ定義 ##############
#define IMG_ITEM_DIR	R"(.\Image\Item)"	//アイテムの画像のディレクトリ

#define IMG_NAME_ITEM01	R"(\item.png)"		//アイテム01の名前
#define IMG_NAME_ITEM02	R"(\item02.png)"	//アイテム02の名前

#define ITEM_TIME_VALUE	5	//増やす時間

//########### クラス定義 ##############
class Item : public Target	//Targetを継承
{

public:

	Item(Image*, Effect*);		//コンストラクタ
	~Item();					//デストラクタ

	void Event(Time*) override;	//クリックされた時の処理

};

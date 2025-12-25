//Toy.hpp
//的（プラスポイント）のクラス

#pragma once

//############## ヘッダファイル読み込み ################
#include "Target.hpp"

//############## マクロ定義 #################
#define IMG_TOY_DIR		R"(.\Image\Toy)"	//おもちゃの画像のディレクトリ

#define IMG_NAME_TOY01	R"(\toy01.png)"		//おもちゃ01の名前
#define IMG_NAME_TOY02	R"(\toy02.png)"		//おもちゃ02の名前
#define IMG_NAME_TOY03	R"(\toy03.png)"		//おもちゃ03の名前

//############## クラス定義 #################
class Toy : public Target	//Targetクラスを継承
{
public:

	Toy(Image*,Effect*);		//コンストラクタ
	~Toy();						//デストラクタ

	void Event(Time*) override;	//クリックされた時の処理

};

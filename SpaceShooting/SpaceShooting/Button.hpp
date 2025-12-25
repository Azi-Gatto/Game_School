//Button.hpp
//ボタンのクラス

#pragma once

//################# ヘッダファイル読み込み ####################
#include "Global.hpp"
#include "Image.hpp"
#include "Music.hpp"

//################# マクロ定義 ################
#define BT_IMG_DIR			R"(.\Image\Button)"	//ボタンの画像のディレクトリ

#define BT_START_IMG_NAME	R"(\start.png)"		//ボタンの画像(start)
#define BT_END_IMG_NAME		R"(\end.png)"		//ボタンの画像(end)

#define BT_START_X	150		//スタートボタンX位置
#define BT_START_Y	500		//スタートボタンY位置
#define BT_END_X	500		//スタートボタンX位置
#define BT_END_Y	500		//スタートボタンY位置

#define RECT_TOUKA_VALUE		0.8	//領域の透過率

//################# 列挙型 #################
enum BT_TYPE
{
	BT_START,		//スタート
	BT_END			//エンド
};

using std::string;
//################# クラス定義 ################
class Button
{
private:

	string text;//文字
	Image* img;	//画像
	RECT rect;	//領域
	static Music* se;	//効果音

public:

	Button(const char*);//コンストラクタ
	Button(Image*);		//コンストラクタ
	~Button();			//デストラクタ

	void SetInit(int,int);	//初期設定

	void UpDate();	//更新処理

	bool OnClick();	//クリックされたか
	void Draw();	//描画
	
	template <typename F>
	void Event(F func)	//クリックされた時のイベント
	{
		func();
	}

};

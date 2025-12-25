//Title.hpp
//タイトル画面の処理

#pragma once

//################### ヘッダファイル読み込み ################
#include "Scene.hpp"
#include "Button.hpp"

//################### マクロ定義 #####################
#define TITLE_TEXT	"NowTitle"			//タイトル画面のテキスト

//################### クラス定義 #####################
class Title : public Scene	//Sceneクラスを継承
{
private:

	vector<Image*> bt_img;	//ボタンの画像
	vector<Button*> button;	//ボタン

	void ButtonFunc();	//ボタン毎の処理

public:

	Title();		//コンストラクタ 
	~Title();		//デストラクタ

	void SetInit() override;	//初期設定
	void PlayScene() override;	//タイトル画面の処理

};

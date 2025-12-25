//Load.hpp
//読み込み画面のクラス（Sceneクラスから派生）

#pragma once

//################### ヘッダファイル読み込み #################
#include "Scene.hpp"
#include "Animation.hpp"

//################### マクロ定義 ###################
#define DEFF_FONT_SIZE		24		//通常のフォントサイズ
#define PLAY_FONT_SIZE		48		//ゲームプレイ中のフォントサイズ

#define LOAD_TEXT			"NowLoading…"		//ロード画面のテキスト
#define DISCRIPTION_TEXT	"右クリックで弾を発射できるよ！\n敵機が自機に当たるか、画面端まで来てしまうと\nゲームオーバーだ！\n敵機を沢山撃ち落とそう！" //説明テキスト
#define PUSH_TEXT			"左クリックでSTART!"		//クリックのテキスト
//座標関係
#define DISCRIPTION_X	50	//説明用のテキスト描画X位置
#define DISCRIPTION_Y	50	//説明用のテキスト描画Y位置

//################### クラス定義 ###################
class Load : public Scene	//Sceneクラスを継承
{
private:

public:

	Load();		//コンストラクタ 
	~Load();	//デストラクタ

	void SetInit() override;	//初期設定
	void PlayScene() override;	//ロード画面の処理

};

//Play.hpp
//プレイ画面の処理

#pragma once

//############### ヘッダファイル読み込み ##############
#include "Scene.hpp"
#include "Toy.hpp"
#include "Bomb.hpp"
#include "Item.hpp"

//############### マクロ定義 #################
#define GAME_LIMIT_DRAW_X	680		//ゲームの制限時間描画X位置
#define GAME_LIMIT_DRAW_Y	10		//ゲームの制限時間描画Y位置
#define GAME_LIMIT_TIME		60		//ゲームの制限時間

using std::vector;

//############### クラス定義 #################
class Play : public Scene	//Sceneクラスを継承
{
private:

	vector<Target*> target;		//的
	vector<Image*> tg_img;		//的の画像
	vector<Effect*> tg_effect;	//的のエフェクト
	vector<Animation*> eff_anim;//アニメーション
	vector<Music*> eff_se;		//効果音
	Time* limit;				//制限時間

	bool StartFlg;	//Start()を行ったか

public:

	Play();		//コンストラクタ
	~Play();			//デストラクタ

	void SetInit() override;	//初期設定
	bool DataLoad() override;	//データ読込
	void Run() override;	//プレイ画面の処理
	void Start();			//シーンが変わって一回目だけ行う処理

};

//Play.hpp
//プレイ画面の処理

#pragma once

//############### ヘッダファイル読み込み ##############
#include "Scene.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

//############### マクロ定義 #################
#define PLAY_TEXT	"NowPlay"			//プレイ画面のテキスト

//##################### 列挙型 ##################
enum CHARA_KIND
{
	CHARA_KIND_PLAYER,	//プレイヤー
	CHARA_KIND_ENEMY1,	//敵1
	CHARA_KIND_ENEMY2,	//敵2
	CHARA_KIND_ENEMY3,	//敵3
	CHARA_KIND_ENEMY4,	//敵4
	CHARA_KIND_ENEMY5,	//敵5
	CHARA_KIND_ENEMY6	//敵6
};

//############### クラス定義 #################
class Play : public Scene	//Sceneクラスを継承
{
private:

	vector<Image*> chara_img;	//キャラの画像
	vector<Enemy*> enemy;		//敵
	Player* player;				//プレイヤー

	bool start;					//Start()を実行したか
	void Start();				//シーンが変わったら、一回だけ実行する

public:

	Play();		//コンストラクタ
	~Play();	//デストラクタ

	void SetInit() override;	//初期設定
	void PlayScene() override;	//プレイ画面の処理

};

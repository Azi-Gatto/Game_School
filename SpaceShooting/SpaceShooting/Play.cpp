//Play.cpp
//プレイ画面の処理

//################# ヘッダファイル読み込み #################
#include "Play.hpp"

//################ クラス定義 ################

//コンストラクタ
Play::Play()
{

	if (!back->Load(IMG_DIR_BACK, IMG_NAME_PLAY)) { IsLoad = false; return; }	//背景画像読み込み
	if (!bgm->Load(MUSIC_DIR_BGM, BGM_NAME_PLAY)) { IsLoad = false; return; }	//BGM読み込み

	//キャラ関係
	//画像
	chara_img.push_back(new Image(CHAR_IMG_DIR, PLAYER_IMG_NAME));	//プレイヤーの画像
	chara_img.push_back(new Image(CHAR_IMG_DIR, ENEMY1_IMG_NAME));	//敵1の画像
	chara_img.push_back(new Image(CHAR_IMG_DIR, ENEMY2_IMG_NAME));	//敵2の画像
	chara_img.push_back(new Image(CHAR_IMG_DIR, ENEMY3_IMG_NAME));	//敵3の画像
	chara_img.push_back(new Image(CHAR_IMG_DIR, ENEMY4_IMG_NAME));	//敵4の画像
	chara_img.push_back(new Image(CHAR_IMG_DIR, ENEMY5_IMG_NAME));	//敵5の画像
	chara_img.push_back(new Image(CHAR_IMG_DIR, ENEMY6_IMG_NAME));	//敵6の画像

	for (auto c : chara_img)
	{
		if (!c->GetIsLoad()) { IsLoad = false; return; }	//読み込み失敗
	}
	//キャラ
	enemy.push_back(new Enemy(chara_img.at(CHARA_KIND_ENEMY1)));	//敵1
	enemy.push_back(new Enemy(chara_img.at(CHARA_KIND_ENEMY2)));	//敵2
	enemy.push_back(new Enemy(chara_img.at(CHARA_KIND_ENEMY3)));	//敵3
	enemy.push_back(new Enemy(chara_img.at(CHARA_KIND_ENEMY4)));	//敵4
	enemy.push_back(new Enemy(chara_img.at(CHARA_KIND_ENEMY5)));	//敵5
	enemy.push_back(new Enemy(chara_img.at(CHARA_KIND_ENEMY6)));	//敵6
	for (auto e : enemy)
	{
		if (!e->GetIsLoad()) { IsLoad = false; return; }	//読み込み失敗
	}

	player = new Player(chara_img.at(CHARA_KIND_PLAYER));//プレイヤー
	IsLoad = true;	//読み込み成功
	start = false;	

}

//デストラクタ
Play::~Play()
{
	delete player;	//player破棄
	
	//敵
	for (auto e : enemy) { delete e; }	//delete破棄
	vector<Enemy*> v;
	enemy.swap(v);
}

//初期設定
void Play::SetInit()
{
	back->SetInit();	//画像初期設定
	bgm->SetInit(DX_PLAYTYPE_LOOP, 30);		//BGM初期設定

	//キャラ
	for (auto c : enemy) { c->SetInit(); }
	player->SetInit();
}

//プレイ画面の処理
void Play::PlayScene()
{

	Start();		//シーンが変わったら一回だけ実行

	bgm->Play();	//BGMを流す

	back->Draw(GAME_LEFT, GAME_TOP);	//背景描画

	for (auto e : enemy) 
	{ 
		e->UpDate(player);	//毎回行う処理
	}	

	player->UpDate();		//毎回行う処理

	if (Enemy::GetIsEnd())	//終了したら
	{
		bgm->Stop();			//BGMを止める
		start = false;			//次に備えて、falseへ
		NowScene = SCENE_END;	//エンド画面へ
	}

}

//シーンが変わったら一回だけ実行
void Play::Start()
{
	if (!start)	//処理を実行していなければ
	{
		//敵の初期化
		for (auto e : enemy)
		{
			e->Init();	//初期化
		}

		//プレイヤー初期化
		player->Init();	//初期化
		start = true;	//実行済み
	}
}

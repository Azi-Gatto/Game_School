//Scene.hpp
//各シーンの基になるクラス

#pragma once

//################### ヘッダファイル読み込み ######################
#include "Global.hpp"
#include "Mouse.hpp"
#include "Image.hpp"
#include "Music.hpp"

//################### マクロ定義 #########################

//座標関係
#define TEST_TEXT_X	30					//テスト用のテキスト描画X位置
#define TEST_TEXT_Y	30					//テスト用のテキスト描画Y位置

//################### 列挙型 #####################
enum GAME_SCENE
{
	SCENE_LOAD,			//ロードシーン
	SCENE_TITLE,		//タイトルシーン
	SCENE_PLAY,			//プレイシーン
	SCENE_END			//エンドシーン
};

using std::vector;

//################### クラス定義 #########################
class Scene
{
protected:

	static int NowScene;		//現在のシーン
	static bool GameEnd;		//ゲーム終了フラグ
	static Mouse* mouse;		//マウス
	static bool IsGameStart;	//ゲームスタートできるか
	Image* back;				//背景画像
	Music* bgm;					//BGM
	bool IsLoad;				//読み込めたか

public:

	Scene();		//コンストラクタ
	~Scene();		//デストラクタ

	static int GetNowScene();	//現在のシーンを取得
	static bool IsGameEnd();	//ゲームエンドフラグを取得
	static bool GetIsGameStart();//ゲームスタートできるか取得
	bool GetIsLoad();			//読み込めたか取得

	virtual void SetInit() = 0;		//初期設定
	virtual void PlayScene() = 0;	//シーン毎の処理

};

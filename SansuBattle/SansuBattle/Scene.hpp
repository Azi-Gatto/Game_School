//Scene.hpp
//各シーンの基になるクラス

#pragma once

//################### ヘッダファイル読み込み ######################
#include "Global.hpp"
#include "Image.hpp"
#include "Music.hpp"
#include "Font.hpp"
#include "Data.hpp"
#include "Save.hpp"
#include "Score.hpp"

//################### マクロ定義 #########################

//################### 列挙型 #####################
enum GAME_SCENE
{
	SCENE_LOAD,			//ロードシーン
	SCENE_TITLE,		//タイトルシーン
	SCENE_SELECT,		//選択シーン
	SCENE_PLAY,			//プレイシーン
	SCENE_RANKING		//ランキングシーン
};

enum GAMEMODE_KIND
{
	GAMEMODE_SUM,					//モード、和（足し算）
	GAMEMODE_DIFFERENCE,			//モード、差（引き算）
	GAMEMODE_PRODUCT,				//モード、積（掛け算）
	GAMEMODE_DEALER,				//モード、商（割り算）
	GAMEMODE_SUM_DIF,				//モード、和差（足し算、引き算）
	GAMEMODE_PRO_DEA,				//モード、積商（掛け算、割り算）
	GAMEMODE_SUM_PRO,				//MODE(+*)
	GAMEMODE_SUM_DEA,				//MODE(+/)
	GAMEMODE_DIF_PRO,				//MODE(-*)
	GAMEMODE_SUM_DIF_PRO,			//MODE(+-*)
	GAMEMODE_SUM_DIF_DEA,			//MODE(+-/)
	GAMEMODE_ALL,					//MODE(+-*/)
	GAMEMODE_MAX					//ゲームモードの種類数
};	//問題の種類

enum GAME_LEVEL
{
	GAME_LEVEL_EASY,		//簡単
	GAME_LEVEL_NORMAL,		//普通
	GAME_LEVEL_HARD,		//難しい
	GAME_LEVEL_MAX			//ゲームレベルの種類数
};	//ステージのレベル

using std::vector;

//################### クラス定義 #########################
class Scene
{
protected:

	//クラス共通
	static int NowScene;		//現在のシーン
	static int GameMode;		//ゲームモード
	static int GameLevel;		//ゲームレベル
	static bool GameEnd;		//ゲーム終了フラグ
	static vector<Font*> font;	//フォント
	static vector<Data*> data;	//データ

	static bool FadeOut();		//フェードアウト処理
	virtual void Start();		//シーンが変わるごとに1回だけ行う処理

	//インスタンス毎
	Image* back;			//背景画像
	vector<Music*> bgm;		//BGM
	bool IsLoad;			//読み込めたか
	bool start;				//Start処理を行ったか

public:

	Scene();		//コンストラクタ
	~Scene();		//デストラクタ

	static int GetNowScene();	//現在のシーンを取得
	static bool IsGameEnd();	//ゲームエンドフラグを取得

	virtual void SetInit() = 0;	//初期設定
	virtual void Run() = 0;		//シーン毎の処理

};

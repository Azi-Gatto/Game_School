//GameManeger.hpp
//ゲームのシステムを管理するクラス

#pragma once

//############### ヘッダファイル読み込み ##################
#include "Global.hpp"
#include "Fps.hpp"
#include "KeyDown.hpp"
#include "Image.hpp"
#include "Select.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Question.hpp"
#include "Score.hpp"
#include "Font.hpp"
#include "Time.hpp"
#include "Effect.hpp"
#include "Music.hpp"
#include "SaveData.hpp"
#include <typeinfo>

//############### マクロ定義 ################
//テキスト関係
#define LOAD_TEXT			"NowLoading…"		//ロード画面のテキスト
#define PUSH_TEXT			"PushEnter"			//エンターキーを押す、のテキスト
#define TITLE_TEXT			"NowTitle"			//タイトル画面のテキスト
#define CHOISELEVEL_TEXT	"ChoiseLevel"		//難易度選択画面のテキスト
#define CHOISESTAGE_TEXT	"ChoiseStage"		//ステージ選択画面のテキスト
#define PLAY_TEXT			"NowPlay"			//プレイ画面のテキスト
#define DRAWSCORE_TEXT		"DrawScore"			//スコア表示画面のテキスト
#define END_TEXT			"NowEnd"			//エンド画面のテキスト

//座標関係
#define TEST_TEXT_X	0					//テスト用のテキスト描画X位置
#define TEST_TEXT_Y	0					//テスト用のテキスト描画Y位置

//############### 列挙型 ################
enum GAME_SCENE
{
	SCENE_LOAD,			//ロードシーン
	SCENE_TITLE,		//タイトルシーン
	SCENE_SELECT_MODE,	//ゲームモード選択シーン
	SCENE_SELECT_LEVEL,	//レベル選択シーン
	SCENE_PLAY,			//プレイシーン
	SCENE_DRAWSCORE		//スコア表示シーン
	//SCENE_END			//エンドシーン
};

//############### クラス定義 ################
class GameManeger
{

private:

	Fps *fps;					//fps
	KeyDown *keydown;			//キーボード関係
	vector<Image*> back;		//背景画像
	vector<Image*> gamemode_img;//ゲームモードの画像
	Select* select_gamemode;	//ゲームモード選択肢
	vector<Image*> gamelevel_img;//レベルの画像
	Select* select_level;		//レベル選択肢
	Player* player;				//プレイヤー
	vector<Enemy*> enemy;		//敵キャラ
	Question* question;			//問題
	vector<Font*> font;			//フォント
	Time* gamelimittime;		//ゲーム制限時間
	vector<Effect*> effect_atk;	//攻撃エフェクト
	vector<Music*> bgm;			//BGM
	vector<Music*> bgm_play;	//プレイ画面のBGM
	vector<Music*> effect_se;	//エフェクトの効果音
	vector<Music*> play_se;		//プレイ画面の効果音
	Score* score;				//スコア
	SaveData* save;				//セーブデータ
	Select* select_start;		//スタートの選択肢
	vector<Image*> start_img;	//スタートの画像
	
	int NowScene;				//現在のシーン
	int GameMode;				//ゲームのモード
	int GameLevel;				//ゲームレベル
	bool IsLoad;				//読み込みが終わったか
	bool GameEndFlg;			//ゲーム終了フラグ

public:

	GameManeger();				//コンストラクタ
	~GameManeger();				//デストラクタ

	bool Load();				//ゲームに使用するデータの読み込み処理
	bool GameMainLoop();		//ゲームのメインループ

	void ProcesScene();			//各シーンの処理
	void SetInit();				//初期設定


	//****************** シーン関係 *************************
	void Scene_Load();				//ロード画面の処理
	void Draw_Scene_Load();			//ロード画面の描画処理

	void Scene_Title();				//タイトル画面の処理
	void Draw_Scene_Title();		//タイトル画面の描画処理

	void Scene_ChoiseGameMode();		//ゲームモード選択画面の処理
	void Draw_Scene_ChoiseGameMode();	//ゲームモード選択画面の描画処理

	void Scene_ChoiseLevel();		//レベル選択画面の処理
	void Draw_Scene_ChoiseLevel();	//レベル選択画面の描画処理

	void Scene_Play();				//プレイ画面の処理
	void Draw_Scene_Play();			//プレイ画面の描画処理

	void Scene_DrawScore();			//スコア表示画面の処理
	void Draw_SceneDrawScore();		//スコア表示画面の描画処理
		
	//void Scene_End();				//エンド画面の処理
	//void Draw_Scene_End();			//エンド画面の描画処理

};

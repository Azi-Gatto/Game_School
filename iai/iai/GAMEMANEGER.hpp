//GAMEMANEGER.hpp
//ゲームのシステムを管理するクラス

#pragma once

//############### ヘッダファイル読み込み ##################
#include "DxLib.h"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "IMAGE.hpp"
#include "PLAYER.hpp"
#include "ENEMY.hpp"
#include "MUSIC.hpp"
#include "EFFECT.hpp"
#include "FONT.hpp"
#include "SAVEDATA.hpp"

//############### マクロ定義 ################
#define GAME_LEFT	  0		//画面の横の始点
#define GAME_TOP	  0		//画面の縦の始点
#define GAME_WIDTH	880		//画面の横の大きさ
#define GAME_HEIGHT	640		//画面の縦の大きさ

#define GAME_FPS_SPEED					   60

//テキスト関係
#define LOAD_TEXT	"NowLoading…"		//ロード画面のテキスト
#define PUSH_TEXT	"Enterで次へ"		//エンターキーを押す、のテキスト
#define SETUMEI_TEXT "ゲームの遊び方\n画面にマークが表示されたら\nEnterを押そう！"	//説明テキスト
#define TITLE_TEXT	"試合開始"			//タイトル画面のテキスト
#define PLAY_TEXT	"NowPlay"			//プレイ画面のテキスト
#define END_TEXT	"NowEnd"			//エンド画面のテキスト

#define RESULT_WIN_TEXT		"勝利"		//勝った時のテキスト
#define RESULT_LOSE_TEXT	"敗北"		//負けた時のテキスト
#define RESLUT_DRAW_TEXT	"引き分け"	//引き分けの時のテキスト
#define RESULT_OTETUKI_TEXT	"お手付き"	//お手付きの時のテキスト
#define WIN_NUM_DRAW_TEXT	"%d人抜き"	//勝ち数表示のテキスト

#define FORMAT_KEY_WORD		'%'			//書式指定子を検索するときのキーワード
#define FORMAT_REPLACE_NUM	2			//書式指定子を置換するときの文字数

//座標関係
#define TEST_TEXT_X	30					//テスト用のテキスト描画X位置
#define TEST_TEXT_Y	30					//テスト用のテキスト描画Y位置
#define RESULT_TEXT_Y	5				//結果描画Y位置
#define DRAW_WIN_NUM_Y	120				//勝ち数の描画Y位置
#define TITLE_TEXT_Y	400				//タイトル画面のテキスト描画Y位置

//色関係
#define COLOR_RED	GetColor(255,0,0)		//赤色
#define COLOR_GREEN	GetColor(0,255,0)		//緑色
#define COLOR_BLUE	GetColor(0,0,255)		//青色
#define COLOR_WHITE GetColor(255,255,255)	//白色
#define COLOR_BLACK GetColor(0,0,0)			//黒色

#define GAME_START_WAITTIME_MIN		3		//ゲーム開始までの待ち時間の最低値
#define GAME_START_WAITTIME_MAX		8		//ゲーム開始までの待ち時間の最大値

//############### 列挙型 ################
enum GAME_SCENE
{
	SCENE_LOAD,			//ロードシーン
	SCENE_TITLE,		//タイトルシーン
	SCENE_PLAY,			//プレイシーン
	SCENE_END			//エンドシーン
};

enum PLAY_STAGE
{
	PLAY_STAGE_TEXT_DRAW,		//テキスト表示段階
	PLAY_STAGE_MAIN,			//ゲームプレイ段階
	PLAY_STAGE_RESULT			//結果表示段階
};

//############### クラス定義 ################
class GAMEMANEGER
{

private:

	FPS *fps;					//fps
	KEYDOWN *keydown;			//キーボード関係
	IMAGE *back;				//背景画像
	IMAGE *mark;				//マーク画像
	PLAYER *player;				//プレイヤー
	ENEMY *enemy;				//敵
	MUSIC *se;					//SE
	MUSIC *bgm;					//BGM
	EFFECT *effect;				//エフェクト
	FONT *font;					//フォント
	SAVEDATA *save;				//セーブデータ

	int NowScene;				//現在のシーン
	bool IsLoad;				//読み込みが終わったか

	int StartTime;				//計測開始時間
	int WaitTime;				//待ち時間
	bool GameStartFlg;			//ゲームが始まったか

	int Play_NowStage;			//プレイシーンの現在の段階

	bool PushFlg;				//キーを押したか

public:

	GAMEMANEGER();				//コンストラクタ
	~GAMEMANEGER();				//デストラクタ

	bool Load();				//ゲームに使用するデータの読み込み処理
	void SetSize();				//画像などのサイズを取得し、設定する
	void SetInit();				//初期設定をする
	bool GameMainLoop();		//ゲームのメインループ

	void ProcesScene();			//各シーンの処理


	//****************** シーン関係 *************************
	void Scene_Load();			//ロード画面の処理
	void Draw_Scene_Load();		//ロード画面の描画処理

	void Scene_Title();			//タイトル画面の処理
	void Draw_Scene_Title();	//タイトル画面の描画処理

	void Scene_Play();			//プレイ画面の処理
	void Draw_Scene_Play();		//プレイ画面の描画処理

	void Scene_End();			//エンド画面の処理
	void Draw_Scene_End();		//エンド画面の描画処理

	//******************** プレイ画面で使用する処理関係 ***********************
	bool WaitStartTime();		//スタート時間まで待つ
	void PlayReset();			//プレイ画面で使用するものをリセット
	void Judg();				//どちらが勝ったか判定
	void PlayStage_DrawText();	//プレイ段階、テキスト表示のときの処理
	void PlayStage_Main();		//プレイ段階、ゲーム中のときの処理
	void PlayStage_Result();	//プレイ段階、結果表示のときの処理


	void DrawTextCenter(int,const char *,unsigned int color=COLOR_BLACK);	//渡された文字列を画面中央に描画する(高さは自分で指定する)
	void DrawTextCenter(const char*, unsigned int color = COLOR_BLACK);		//渡された文字列を画面中央に描画する(上下左右、中央)
	void DrawNumTextCenter(int, const char *, int);							//書式付き(数字)文字列を中央に描画する(高さは自分で指定する)

	void Save();	//セーブ

};

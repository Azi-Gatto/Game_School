/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.hpp     																				　 */
/*       																						　 */

#pragma once

//########## ヘッダーファイル読み込み ##########


//########## マクロ定義 ##########
#define GAME_LEFT	  0		//画面の横の始点
#define GAME_TOP	  0		//画面の縦の始点
#define GAME_WIDTH	880		//画面の横の大きさ
#define GAME_HEIGHT	640		//画面の縦の大きさ
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_NAME	"LEGEND STORY"		//ウィンドウのタイトル
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE：ウィンドウモード / FALSE：フルスクリーン

#define SET_WINDOW_ST_MODE_DEFAULT			0	//デフォルト
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//タイトルバーなし
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//タイトルバーとフレームなし
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//フレームなし

#define GAME_FPS_SPEED					   60

#define GAME_WAITCNT_MAX				   60	//待ち時間のカウントマックス値

#define GAME_ICON_ID					   333	//アイコンのID

#define ENCOUNT_TXT_KIND	3	//エンカウント時のテキストの種類

//テキスト関係
#define LOAD_TEXT				"Now Loading・・・"		//ロード時のテキスト
#define SAVE_TEXT				"セーブ中です。"		//セーブ時のテキスト
#define GAME_CLEAR_TEXT			"ゲームクリア！"		//ゲームクリア時のテキスト
#define GAME_OVER_TEXT			"ゲームオーバー…"		//ゲームオーバー時のテキスト

#define ENCOUNT_TEXT_1			"バイト帰りの"			//敵に遭遇した時のテキスト1個め
#define ENCOUNT_TEXT_2			"肥満体の"				//敵に遭遇した時のテキスト2個め
#define ENCOUNT_TEXT_3			"疲れ果てた"			//敵に遭遇した時のテキスト3個め
#define ENCOUNT_AF_TEXT			"が現れた！"			//敵に遭遇した時の敵の名前の後ろにつけるテキスト

#define BT_WAIT_ACT_TEXT		"どうする？"			//戦闘画面でプレイヤー行動待ち状態に表示されるテキスト

#define TITLE_SELECT_START_TEXT	"スタート"				//タイトルの選択肢（ゲームスタート）のテキスト
#define TITLE_SELECT_END_TEXT	"おわる"				//タイトルの選択肢（ゲーム終了）のテキスト

#define END_SELECT_TITLE_TEXT	"タイトル"				//エンド画面の選択肢（タイトルへ戻る）のテキスト
#define END_SELECT_END_TEXT		"おわる"				//エンド画面の選択肢（ゲーム終了）のテキスト

#define MGC_SELECT_MP_TEXT		"MP:"					//魔法一覧の選択肢のMP表示のテキスト

#define BT_ESCAPE_TEXT			"上手く逃げ切れた！"	//戦闘時に逃げるを選んだときのテキスト
#define BT_DEF_TEXT_1			"は防御している！"		//戦闘時に防御を選んだときのテキスト1個め
#define BT_DEF_TEXT_2			"防御に集中している！"	//戦闘時に防御を選んだときのテキスト2個め
#define BT_ITEM_TEXT_1			"を使用した！"			//戦闘時にアイテムを選んだときのテキスト1個目
#define BT_ITEM_TEXT_HP			"HPが"					//戦闘時に使用したアイテムがHP回復のものだった時のテキスト
#define BT_ITEM_TEXT_MP			"MPが"					//戦闘時に使用したアイテムがMP回復のものだった時のテキスト
#define BT_ITEM_TEXT_2			"回復した！"			//戦闘時にアイテムを選んだときのテキスト2個目
#define BT_ATK_TEXT				"の攻撃！"				//戦闘時の攻撃テキスト
#define BT_ATK_RECV_TEXT		"のダメージを受けた！"	//戦闘時にダメージを受けたときのテキスト
#define BT_ATK_SEND_TEXT		"のダメージを与えた！"	//戦闘時にダメージを与えたときのテキスト
#define BT_LOSE_TEXT			"全滅してしまった…"	//戦闘時に全滅した時のテキスト

#define BT_RESULT_TEXT			"を倒した！"			//戦闘に勝った時のテキスト
#define BT_DROP_MIDLE_TEXT		"は、"					//ドロップメッセージの真ん中に入れるテキスト
#define BT_DROP_AF_TEXT			"を落としていった！"	//ドロップメッセージの後ろに入れるテキスト
#define BT_DROP_GET_TEXT		"を手に入れた！"		//ドロップメッセージ
#define BT_RESULT_GET_EXP_TEXT	"の経験値を手に入れた！"//手に入れた経験値を表示するときのテキスト
#define BT_LEVELUP_BF_TEXT		"レベル"				//レベルアップメッセージの前に入れるテキスト
#define BT_LEVELUP_AF_TEXT		"になった！"			//レベルアップメッセージの後ろに入れるテキスト




//############### 列挙型 ###############
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//タイトル画面
	GAME_SCENE_PLAY,	//プレイ画面
	GAME_SCENE_BATTLE,	//戦闘画面
	GAME_SCENE_END,		//エンド画面
	GAME_SCENE_CHENGE	//シーン遷移画面
};

enum BATTLE_STAGE
{
	WAIT_ACT,			//行動選択待ち状態
	DAMEGE_CALC,		//ダメージ計算状態
	ACT_MSG,			//行動メッセージ表示状態
	DRAW_EFFECT,		//エフェクト表示状態
	DRAW_DAMEGE,		//ダメージ描画状態
	RESULT_MSG			//リザルトメッセージ描画状態
};

enum TURN
{
	MY_TURN,		//味方のターン
	ENEMY_TURN		//敵のターン
};

enum ENCOUNT_TXT_TYPE
{
	ENCOUNT_TXT_PATARN1,	//遭遇した時のテキスト種類1個め
	ENCOUNT_TXT_PATARN2,	//遭遇した時のテキスト種類2個め
	ENCOUNT_TXT_PATARN3		//遭遇した時のテキスト種類3個め
};

enum TITLE_SELECT
{
	TITLE_SELECT_START,	//スタート
	TITLE_SELECT_END	//終了
};

enum END_SELECT
{
	END_SELECT_TITLE,	//タイトルへ
	END_SELECT_END		//終了
};

//############## プロトタイプ宣言 #############

void Load();				//ロード画面の処理
void Title();				//タイトル画面の処理
void Play();				//プレイ画面の処理
void Battle();				//戦闘画面の処理
void End();					//エンド画面の処理
void Chenge();				//シーン遷移画面の処理

void Init();				//初期化処理
void BattleInit();			//戦闘画面関係初期化
void SceneChenge(int, int);	//シーンを変更する処理

void Load_Draw();			//ロード画面の描画処理
void Title_Draw();			//タイトル画面の描画処理
void Play_Draw();			//プレイ画面の描画処理
void Battle_Draw();			//戦闘画面の描画処理
void End_Draw();			//エンド画面の描画処理

void Enconte();				//敵との遭遇処理
bool Wait();				//待つ処理
void Delete_Class();		//クラスを削除する処理
bool LoadGameData();		//ゲームで使用するデータ等を読み込む処理
void SetGameInit();			//ゲームの初期設定を行う処理
void SetSize();				//画像等のサイズ設定を行う処理
bool GameMainLoop();		//無限ループ内のゲーム処理

//戦闘画面の処理
void Bt_WaitAct();			//戦闘画面行動待ち状態の処理
void Bt_DamegeCalc();		//戦闘画面ダメージ計算状態の処理
void Bt_ActMsg();			//戦闘画面行動メッセージ描画状態の処理
void Bt_DrawEffect();		//戦闘画面エフェクト描画状態の処理
void Bt_DrawDamege();		//戦闘画面ダメージ描画状態の処理
void Bt_ResultMsg();		//戦闘画面リザルトメッセージ描画状態の処理

const char * JudgeDrop();	//ドロップした物の種類を判別する

//########## クラスの定義 ##########
//UI.hpp
//ゲーム内で使用するUIを管理するクラス

#pragma once

//######################### ヘッダファイル読み込み #############################
#include "DxLib.h"
#include "PLAYER.hpp"
#include "SELECT.hpp"
#include "LIST_ITEM.hpp"
#include "LIST_ARMOR.hpp"
#include "LIST_WEAPON.hpp"

//######################### マクロ定義 #####################################
#define UI_DIR	R"(.\MY_IMG\Ui\)"	//UI画像のフォルダ名

#define UI_WINDOW_NAME	R"(window.png)"		//ウィンドウの名前

//ステータスウィンドウ関係
#define STA_WIN_X		0				//ステータスウィンドウ描画開始X位置
#define STA_WIN_Y		530				//ステータスウィンドウ描画開始Y位置
#define STA_WIN_WIDTH	350				//ステータスウィンドウの横幅
#define STA_WIN_HEIGHT	110				//ステータスウィンドウの高さ
#define STA_TXT_X		STA_WIN_X + 10	//ステータスの文字の描画開始X位置
#define STA_TXT_Y		STA_WIN_Y + 5	//ステータスの文字の描画開始Y位置
#define STA_SPACE		20				//ステータス文字の間隔
//HPバー
#define STA_HP_BAR_X	90				//HPバーの描画開始X位置
#define	STA_HP_BAR_Y	585				//HPバーの描画開始Y位置
#define	STA_HP_BAR_WIDTH 100			//HPバーの描画幅
#define STA_HP_BAR_HEIGHT 15			//HPバーの描画高さ
//MPバー
#define STA_MP_BAR_X	90				//MPバーの描画開始X位置
#define	STA_MP_BAR_Y	610				//MPバーの描画開始Y位置
#define	STA_MP_BAR_WIDTH 100			//MPバーの描画幅
#define STA_MP_BAR_HEIGHT 15			//MPバーの描画高さ
//BP
#define STA_BP_X		STA_WIN_X + 150			//BPの描画開始X位置
#define STA_BP_Y		STA_WIN_Y + 15			//BPの描画開始Y位置
#define STA_BP_DRAW_SIZE 10						//BPの描画サイズ
#define STA_BP_INTERVAL STA_BP_DRAW_SIZE * 3	//BPの描画間隔

//メニュー一覧
#define MENU_LIST_WIN_X			20		//メニューウィンドウ（一覧）の描画開始X位置
#define MENU_LIST_WIN_Y			20		//メニューウィンドウ（一覧）の描画開始Y位置
#define MENU_LIST_WIN_WIDTH		150		//メニューウィンドウ（一覧）の幅
#define MENU_LIST_WIN_HEIGHT	180		//メニューウィンドウ（一覧）の高さ
#define MENU_LIST_TEXT_X		MENU_LIST_WIN_X + 10	//メニューウィンドウ（一覧）のテキストの描画開始X位置
#define MENU_LIST_TEXT_Y		MENU_LIST_WIN_Y	+ 5		//メニューウィンドウ（一覧）のテキストの描画開始Y位置

//メニュー毎
#define MENU_WINDOW_X	MENU_LIST_WIN_X	+ MENU_LIST_WIN_WIDTH	//選んだメニュー毎のウィンドウの描画開始X位置
#define MENU_WINDOW_Y	MENU_LIST_WIN_Y							//選んだメニュー毎のウィンドウの描画開始Y位置
#define MENU_TEXT_X		MENU_WINDOW_X + 10						//選んだメニュー毎の内容の描画開始X位置
#define MENU_TEXT_Y		MENU_WINDOW_Y + 35						//選んだメニュー毎の内容の描画開始Y位置
#define MENU_TEXT_TOP_Y	MENU_WINDOW_Y + 5						//選んだメニュー毎の先頭要素の描画開始Y位置
#define MENU_WINDOW_WIDTH	700									//選んだメニュー毎のウィンドウの横幅
#define MENU_WINDOW_HEIGHT	500									//選んだメニュー毎のウィンドウの高さ
//ステータス系
#define MENU_STATE_INDEX_X		MENU_WINDOW_X + 20			//ステータス画面の目次要素の描画開始X位置
#define MENU_STATE_INDEX_Y		MENU_WINDOW_Y + 5			//ステータス画面の目次要素の描画開始Y位置
#define MENU_STATE_X			MENU_STATE_INDEX_X + 150	//ステータス画面の各要素の描画開始X位置
#define MENU_STATE_Y			MENU_STATE_INDEX_Y			//ステータス画面の各要素の描画開始Y位置
//アイテム系
#define MENU_ITEM_NAME_SPACE		200		//アイテム画面の名前と所持数の表示間隔
#define MENU_ITEM_POSSESSION_SPACE	70		//アイテム画面の所持数と説明文の表示間隔
//装備系
#define MENU_EQUIP_INDEX_X	MENU_WINDOW_X + 125	//装備画面の武器防具選択肢の描画開始X位置
#define MENU_EQUIP_INDEX_Y	MENU_WINDOW_Y + 5	//装備画面の武器防具選択肢の描画開始Y位置
#define MENU_EQUIPMARK_SIZE			15		//装備マークの大きさ
#define MENU_EQUIP_NAME_SPACE		200		//装備画面の名前と所持数の表示間隔
#define MENU_EQUIP_POSSESSION_SPACE	50		//装備画面の所持数と上昇値の表示間隔

//バトルコマンド関係
#define CMD_WIN_X		350				//バトルコマンドのウィンドウの描画開始X位置
#define	CMD_WIN_Y		530				//バトルコマンドのウィンドウの描画開始Y位置
#define CMD_WIN_WIDTH	120				//バトルコマンドのウィンドウの横幅
#define CMD_WIN_HEIGHT	110				//バトルコマンドのウィンドウの高さ
#define CMD_TXT_X		CMD_WIN_X + 10	//バトルコマンドの文字の描画開始X位置
#define CMD_TXT_Y		CMD_WIN_Y + 5	//バトルコマンドの文字の描画開始Y位置

//魔法一覧関係
#define BT_LIST_WIN_X		470						//魔法一覧のウィンドウの描画開始X位置
#define BT_LIST_WIN_Y		530						//魔法一覧のウィンドウの描画開始Y位置
#define BT_LIST_WIN_WIDTH	100						//魔法一覧のウィンドウの横幅
#define BT_LIST_WIN_HEIGHT	110						//魔法一覧のウィンドウの高さ
#define BT_LIST_TXT_X		BT_LIST_WIN_X + 10		//魔法一覧の文字の描画開始X位置
#define BT_LIST_TXT_Y		BT_LIST_WIN_Y + 5		//魔法一覧の文字の描画開始Y位置

//ウィンドウ関係
#define BT_WINDOW_X		0			//バトル画面のウィンドウの描画開始X位置
#define BT_WINDOW_Y		380			//バトル画面のウィンドウの描画開始Y位置
#define PLAY_WIN_X		0			//プレイ画面のウィンドウの描画開始X位置
#define PLAY_WIN_Y		490			//プレイ画面のウィンドウの描画開始Y位置

#define PLAY_WIN_TEXT_X	PLAY_WIN_X + 20	//プレイ画面のウィンドウ内に描画するテキストの描画開始X位置
#define PLAY_WIN_TEXT_Y	PLAY_WIN_Y + 20	//プレイ画面のウィンドウ内に描画するテキストの描画開始Y位置

//テキストポーズ関係
#define BT_TXT_POSE_Y	500		//バトル画面のテキストポーズの描画Y位置

#define DEFAULT_TEXT_Y	490		//デフォルトのテキスト描画位置（Y座標）
//#define TXT_Y_3			450		//選択肢が3つの時のテキスト描画位置（Y座標）

//テキスト関係
#define MENU_SELECT_STATE_TEXT			"ステータス"		//メニュー画面の選択肢（ステータス）
#define MENU_SELECT_ITEM_TEXT			"アイテム"			//メニュー画面の選択肢（アイテム）
#define MENU_SELECT_EQUIP_TEXT			"装備"				//メニュー画面の選択肢（装備）
#define MENU_SELECT_DESCRIPITON_TEXT	"操作説明"			//メニュー画面の選択肢（操作説明）
#define MENU_SELECT_SAVE_TEXT			"セーブ"			//メニュー画面の選択肢（セーブ）

#define BT_CMD_ATK_TEXT					"こうげき"			//バトルコマンド（攻撃）
#define BT_CMD_DEF_TEXT					"ぼうぎょ"			//バトルコマンド（防御）
#define BT_CMD_MGC_TEXT					"まほう"			//バトルコマンド（魔法）
#define BT_CMD_ITEM_TEXT				"アイテム"			//バトルコマンド（アイテム）
#define BT_CMD_ESC_TEXT					"にげる"			//バトルコマンド（逃げる）

#define SELECT_YES_TEXT					"はい"				//はい、の選択肢
#define SELECT_NO_TEXT					"いいえ"			//いいえの選択肢

#define SELECT_EQUIP_WEAPON_TEXT		"武器"				//武器防具の選択肢の武器のテキスト
#define SELECT_EQUIP_ARMOR_TEXT			"防具"				//武器防具の選択肢の防具のテキスト

#define STATE_INDEX_PLAYERNAME_TEXT		"プレイヤー名"		//ステータス目次（プレイヤー名）
#define STATE_INDEX_LEVEL_TEXT			"Lv"				//ステータス目次（レベル）
#define STATE_INDEX_HP_TEXT				"HP"				//ステータス目次（HP）
#define STATE_INDEX_MP_TEXT				"MP"				//ステータス目次（MP）
#define STATE_INDEX_ATK_TEXT			"攻撃力"			//ステータス目次（攻撃力）
#define STATE_INDEX_DEF_TEXT			"防御力"			//ステータス目次（防御力）
#define STATE_INDEX_SPD_TEXT			"素早さ"			//ステータス目次（素早さ）
#define STATE_INDEX_EXP_TEXT			"Exp"				//ステータス目次（経験値）

//######################### 列挙型 #################################
enum UI_IMAGE_TYPE
{
	UI_WINDOW			//ウィンドウ
};

enum MENU_COMMAND
{
	MENU_STATUS,		//ステータス
	MENU_ITEM,			//アイテム
	MENU_EQUIPMENT,		//装備
	MENU_SETUMEI,		//操作説明
	MENU_SAVE			//セーブ
};

enum MENU_EQUIP_DIR
{
	MENU_EQUIP_SELECT_KIND,		//武器か防具かを選択する段階
	MENU_EQUIP_SELECT_EQUIP,	//装備する武器、もしくは防具を選択する段階
	MENU_EQUIP_SELECT_DECISION	//装備するか選択する段階（はい、か、いいえ）
};

//######################### クラス定義 #####################################
class UI
{
private:

	std::vector<std::string> StateIndex;	//目次要素の文字列

	IMAGE *TextWindow;				//テキストウィンドウの画像

	ANIMATION *TextPose;			//テキストポーズのアニメーション

	bool IsDrawUIAnime;				//UIのアニメーションを描画してよいか

	int Menu_Equip_dir;				//装備画面の選択の段階を管理する変数

public:

	SELECT *MenuSelect;			//メニューの選択肢
	SELECT *BattleCommand;		//バトルコマンドの選択肢
	SELECT *ItemSelect;			//アイテムの選択肢
	SELECT *WeaponSelect;		//武器の選択肢
	SELECT *ArmorSelect;		//防具の選択肢
	SELECT *Yes_No;				//はい、いいえの選択肢
	SELECT *EquipSelect;		//武器か防具かの選択肢
	SELECT *MgcSelect;			//魔法の選択肢

	UI();					//コンストラクタ

	~UI();					//デストラクタ

	//******************** メニュー関係 *************************
	void DrawMenu();							//メニューウィンドウ描画
	void ResetMenu();							//メニュー関係のメンバーをリセット
	int GetMenuEquipDir(void);					//メニューの装備画面の選択肢の段階を取得
	void DrawMenuCheck();						//メニューウィンドウでの確認の選択肢描画

	//ステータス
	void DrawMenuState(PLAYER *);				//メニュー画面のステータス描画処理

	//アイテム
	bool MenuSelectItem(KEYDOWN *, MUSIC *);	//メニューのアイテム画面の処理

	//装備
	int MenuSelectEquip(KEYDOWN *, MUSIC *);	//メニューの装備画面の処理
	void DrawMenuEquip(WEAPON *, ARMOR *);		//メニューの装備描画処理

	//********************** バトル関係 **************************
	void DrawCommand();					//バトルコマンド描画
	void BattleInit();					//バトルコマンドで使用する要素を初期化する
	void DrawStateWindow(PLAYER *);		//ステータスウィンドウ描画

	//************************ ウィンドウ関係 *************************
	void DrawWindow(int, int, int, int);			//ウィンドウを描画する
	void DrawWindow(int,int,int,int,unsigned int);	//ウィンドウを描画する(色指定)
	void DrawWindowFrame(int, int, int, int);		//ウィンドウの枠を描画する

	//************************** UI画像関係 ***************************
	void DrawUiImage(int, int,int);				//UIの画像を描画する
	bool AddUiImage(const char *, const char *);//ui画像を追加する
	int GetUiImageWidth(int);					//ui画像の横幅取得
	int GetUiImageHeight(int);					//ui画像の高さ取得

	//************************ UIアニメーション関係 ****************************
	bool AddUiAnime(const char *, const char *, int, int, int, int, int, double, bool);	//アニメーション画像を追加する
	void DrawUiAnime(int,int);			//アニメーション画像を描画する
	void SetIsDrawUIAnime(bool);		//アニメーション画像を描画してよいか設定
	bool GetIsDrawUIAnime(void);		//アニメーション画像を描画してよいか取得

	//*********************** 設定関係 ***************************
	void Init(void);		//初期化
	void SetSize(void);		//画像サイズを設定する

	//**************************** アイテム関係 ****************************
	void DrawItemSelect(int ,int ,ITEM *);				//アイテムの選択肢を描画する
	void DrawItemSelect(int ,int ,ITEM *,LIST_ITEM *);	//アイテムの選択肢を描画する(説明文付き)

	//***************************** 選択肢関係 *****************************
	void SelectUpdate(ITEM *, LIST_ITEM *);		//選択肢の内容を更新する処理(アイテム)
	void SelectUpdate(WEAPON *, LIST_WEAPON *);	//武器
	void SelectUpdate(ARMOR *, LIST_ARMOR *);	//防具
	void DrawCheck(const char *);				//確認の選択肢を描画する

};

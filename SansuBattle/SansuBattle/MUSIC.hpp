//Music.hpp
//音楽用クラス

#pragma once

//##################### ヘッダファイル読み込み #######################
#include "Global.hpp"

//##################### マクロ定義：ファイルパス、名前 ###################
#define MUSIC_DIR_SE				R"(.\Music\Se)"			//SEのファイル名
#define MUSIC_DIR_BGM				R"(.\Music\Bgm)"		//BGMのファイル名
#define MUSIC_DIR_EFFECT			R"(.\Music\Effect)"		//エフェクトのファイル名

//エフェクト
#define SE_NAME_EF_DAMEGE			R"(\damege.mp3)"		//ダメージエフェクトの効果音

//BGM
#define BGM_NAME_TITLE				R"(\title.mp3)"			//タイトルのBGM
#define BGM_NAME_SELECT				R"(\select.mp3)"		//セレクトのBGM
#define BGM_NAME_RANKING			R"(\ranking.mp3)"		//ランキングのBGM
//********** プレイ画面 **************
#define BGM_NAME_PLAY_SUM			R"(\play_add_bgm.mp3)"			//プレイ画面（+）のBGMの名前
#define BGM_NAME_PLAY_DIF			R"(\play_diff_bgm.mp3)"			//プレイ画面（-）のBGMの名前
#define BGM_NAME_PLAY_PRO			R"(\play_pro_bgm.mp3)"			//プレイ画面（*）のBGMの名前
#define BGM_NAME_PLAY_DEA			R"(\play_dealer_bgm.mp3)"		//プレイ画面（/）のBGMの名前
#define BGM_NAME_PLAY_SUM_DIF		R"(\play_sum_dif_bgm.mp3)"		//プレイ画面（+-）のBGMの名前
#define BGM_NAME_PLAY_PRO_DEA		R"(\play_pro_dea_bgm.mp3)"		//プレイ画面（*/）のBGMの名前
#define BGM_NAME_PLAY_SUM_PRO		R"(\play_sum_pro_bgm.mp3)"		//プレイ画面（+*）のBGMの名前
#define BGM_NAME_PLAY_SUM_DEA		R"(\play_sum_dea_bgm.mp3)"		//プレイ画面（+/）のBGMの名前
#define BGM_NAME_PLAY_DIF_PRO		R"(\play_dif_pro_bgm.mp3)"		//プレイ画面（-*）のBGMの名前
#define BGM_NAME_PLAY_SUM_DIF_PRO	R"(\play_sum_dif_pro_bgm.mp3)"	//プレイ画面（+-*）のBGMの名前
#define BGM_NAME_PLAY_SUM_DIF_DEA	R"(\play_sum_dif_dea_bgm.mp3)"	//プレイ画面（+-/）のBGMの名前
#define BGM_NAME_PLAY_ALL			R"(\play_all_bgm.mp3)"			//プレイ画面（+-*/）のBGMの名前

//SE
#define SE_NAME_KETTEI				R"(\kettei.mp3)"		//決定の効果音
#define SE_NAME_FALSE				R"(\false.mp3)"			//不正解の効果音
#define SE_NAME_PL_DAMEGE			R"(\damege.wav)"		//プレイヤーがダメージを受けたときの効果音

//##################### マクロ定義：エラーメッセージ ######################
#define MUSIC_ERROR_TITLE	"MUSIC_ERROR"					//エラータイトル
#define MUSIC_ERROR_MSG		"音が読み込めませんでした"		//エラーメッセージ

//##################### マクロ定義 ##########################
#define VOLUME_MAX		255	//音量の最大値
#define VOL_DEF			30	//デフォルトの音量(30%)

//##################### 列挙型 #########################
enum EF_SE_NAME
{
	EF_SE_DAMEGE,		//ダメージ
};

using std::string;

//##################### クラス定義 ############################
class Music
{
private:

	string FilePath;		//ファイルパス
	string FileName;		//名前

	int Handle;				//ハンドル
	int PlayType;			//音の再生方法

	bool IsLoad;			//読み込めたか
	bool IsPlayed;			//再生済みか


public:

	Music(const char *, const char *);		//コンストラクタ
	Music();								//コンストラクタ
	~Music();								//デストラクタ

	bool Load(const char*, const char*);	//読み込み

	bool GetIsLoad();						//読み込めたかを取得する
	bool GetIsPlay();						//音が再生されているか取得する
	void SetInit(int, double);				//初期設定

	void ChengePlayType(int);				//音の再生方法を変更する
	void ChengeVolume(double);				//音量を変更する

	void Play(bool check = true);			//音を再生する
	void PlayOne(bool check = true);		//音を再生する(1回だけ)

	void Reset();							//再生済みがどうかをリセットする

	void Stop();							//音を止める

};

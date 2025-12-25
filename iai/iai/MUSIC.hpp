//MUSIC.hpp
//音楽用クラス

/*
追加方法
・フォルダ名、ファイル名をマクロ定義する
・追加した音の種類ごとに、列挙型に追加する
　例：戦闘で使用するSEを追加した場合
    　BT_SE_TYPEに追加する
・Add処理を使用して、SEやBGMを追加することができる
*/

#pragma once

//##################### ヘッダファイル読み込み #######################
#include "DxLib.h"
#include <string>
#include <vector>

//##################### マクロ定義：ファイルパス、名前 ###################
#define MUSIC_DIR_SE		R"(.\MY_MUSIC\SE)"			//SEのファイル名
#define MUSIC_DIR_BGM		R"(.\MY_MUSIC\BGM)"			//BGMのファイル名

#define SE_NAME_GAMESTART	R"(\gamestart.mp3)"		//ゲームスータトのSEの名前
#define SE_NAME_GAMEOVER	R"(\gameover.mp3)"		//ゲームオーバーのSEの名前
#define SE_NAME_TEXT_SE		R"(\text_se.mp3)"		//テキスト表示のSEの名前
#define SE_NAME_SLASH		R"(\slash.mp3)"			//斬る効果音の名前

#define BGM_NAME_TITLE_BGM	R"(\title_bgm.mp3)"		//タイトルのBGMの名前
#define BGM_NAME_END_BGM	R"(\end_bgm.mp3)"		//エンド画面のBGMの名前

//##################### マクロ定義：エラーメッセージ ######################
#define MUSIC_ERROR_TITLE "MUSIC_ERROR"					//エラータイトル
#define MUSIC_ERROR_MSG	"音が読み込めませんでした"		//エラーメッセージ

//##################### マクロ定義 ##########################
#define VOLUME_MAX		255	//音量の最大値

//##################### 列挙型 #########################
enum SE_TYPE
{
	SE_TYPE_GAMESTART,		//ゲームスタート
	SE_TYPE_RESULT,			//結果表示
	SE_TYPE_TEXT,			//テキスト表示
	SE_TYPE_SLASH			//斬る音
};

enum BGM_TYPE
{
	BGM_TYPE_TITLE,			//タイトルBGM
	BGM_TYPE_END			//エンドBGM
};

//##################### クラス定義 ############################
class MUSIC
{
private:

	std::string FilePath;		//ファイルパス
	std::string FileName;		//名前

	std::vector<int> Handle;	//ハンドル
	int PlayType;				//音の再生方法

	bool IsLoad;				//読み込めたか
	std::vector<bool> IsPlayed;	//再生済みか


public:

	MUSIC(const char *, const char *);		//コンストラクタ

	~MUSIC();								//デストラクタ

	bool GetIsLoad();						//読み込めたかを取得する
	bool GetIsPlay(int);					//音が再生されているか取得する

	void ChengePlayType(int);				//音の再生方法を変更する
	void ChengeVolume(double,int);			//音量を変更する

	void Play(int);							//音を再生する
	void PlayOne(int);						//音を再生する(1回だけ)

	void PlayReset(int);					//再生済みかどうかをリセットする(指定されたものだけ)
	void PlayReset();						//再生済みがどうかをリセットする(全て)

	void Stop();							//音を止める(全て)
	void Stop(int);							//音を止める(指定されたものだけ)

	bool Add(const char*, const char*);		//音を追加する

};

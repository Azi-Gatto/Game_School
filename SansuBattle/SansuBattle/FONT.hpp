//Font.hpp
//フォントクラス

/*
追加方法
・フォントのファイル名と、フォントの名前をマクロ定義する
・マクロ定義されているフォントの種類を増やす
・Add処理を使用して、ゲーム内で使用するフォントを増やすことができる
*/

#pragma once

//################# ヘッダファイル読み込み ######################
#include "Global.hpp"
#include <string>
#include <vector>

//################ マクロ定義 ファイルパスと名前 ###############
#define FONT_DIR			R"(.\Font)"				//フォントファイルの場所

#define FONT_FNAME_KOKUBAN	R"(\kokubanB.ttf)"			//フォントの名前(黒板)
#define FONT_FNAME_POP		R"(\HGRPP1002.ttf)"			//フォントの名前(ポップ体)
//############### マクロ定義 ##################

//*********** フォント名 **************
#define FONT_NAME_KOKUBAN	"こくばん"					//フォントの正式名称(黒板)
#define FONT_NAME_POP		"創英角ﾎﾟｯﾌﾟ体"				//フォントの正式名称(ポップ)

//*********** フォントサイズ **************
#define F_SIZE_NORMAL	114			//通常のフォントサイズ
#define F_SIZE_TIME		100			//時間表示のフォントサイズ
#define F_SIZE_MINI		90			//フォントサイズ（ミニ）
#define F_SIZE_RANKING	54			//ランキング描画の時のフォントサイズ

//************* フォントの太さ *****************
#define F_BOLD_NORMAL	5			//通常のフォントの太さ

//################ マクロ定義 エラーメッセージ #################
#define FONT_ERROR_TITLE "FONT_ERROR"						//エラータイトル
#define FONT_ERROR_MSG	"フォントが読み込めませんでした"	//エラーメッセージ

//################ 列挙型 #####################
enum LOAD_FONT_NAME
{
	FNAME_KOKUBAN,	//こくばんフォント
	FNAME_POP,		//ポップフォント
	F_MAX			//フォントの数
};	//読み込んだフォントの種類

enum FONT_HANDLE_TYPE
{
	HDL_NR,		//こくばんフォントのノーマルサイズのハンドル
	HDL_MINI,	//ミニサイズのハンドル
	HDL_RANK,	//こくばんフォントのランキング描画サイズのハンドル
	HDL_NR_POP	//ノーマルハンドル（ﾎﾟｯﾌﾟ体）
};

using std::vector;
using std::string;

//################ クラスの定義 ##################
class Font {

private:
	static vector<string> FilePath;			//パス
	static vector<string> LoadFontName;		//読み込んだフォントの名前

	int Handle;								//フォントハンドル
	bool IsCreate;							//作成できたか

	static int NowFont;						//現在のフォントハンドル

	static bool LoadFont(const char*, const char*, const char*);	//フォントを読み込み

public:

	Font(int, int, int, int, 
		int charset = -1,
		int edgesize = -1,
		int ltalic = 0,
		int handle = -1);		//コンストラクタ
	~Font();	//デストラクタ

	static bool ReleaseFont();		//読み込んだフォントを開放
	bool GetIsCreate();				//作成できたか取得
	void Chenge();					//フォントハンドルを変更
	static int GetNowHandle();		//現在のハンドルを取得
};

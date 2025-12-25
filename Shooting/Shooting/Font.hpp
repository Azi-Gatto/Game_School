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

#define FONT_FILE_NAME		R"(\HGRGY003.ttf)"			//フォントの名前
//############### マクロ定義 ##################

//*********** フォント名 **************
#define FONT_NAME		"HGS行書体"					//フォントの正式名称

//*********** フォントサイズ **************
#define F_SIZE_NORMAL	128			//通常のフォントサイズ
#define F_SIZE_MINI		36			//フォントサイズ（ミニ）
#define F_SIZE_RANKING	42			//ランキング描画の時のフォントサイズ

//************* フォントの太さ *****************
#define F_BOLD_NORMAL	5			//通常のフォントの太さ

#define F_EDGE_SIZE		3			//縁取りの太さ

//################ マクロ定義 エラーメッセージ #################
#define FONT_ERROR_TITLE "FONT_ERROR"						//エラータイトル
#define FONT_ERROR_MSG	"フォントが読み込めませんでした"	//エラーメッセージ

//################ 列挙型 #####################
enum LOAD_FONT_NAME
{
	F_NAME_HGS	//HGS行書体
};	//読み込んだフォントの種類

enum FONT_HANDLE_TYPE
{
	FH_NORMAL,	//HGS行書体のノーマルサイズのハンドル
	FH_MINI,	//ミニサイズのハンドル
	FH_RANKING	//こくばんフォントのランキング描画サイズのハンドル
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

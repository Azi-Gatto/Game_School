//FONT.hpp
//フォントクラス

/*
追加方法
・フォントのファイル名と、フォントの名前をマクロ定義する
・マクロ定義されているフォントの種類を増やす
・Add処理を使用して、ゲーム内で使用するフォントを増やすことができる
*/

#pragma once

//################# ヘッダファイル読み込み ######################
#include "DxLib.h"
#include <string>
#include <vector>

//################ マクロ定義 ファイルパスと名前 ###############
#define FONT_DIR			R"(.\MY_FONT)"				//フォントファイルの場所

#define FONT_FILE_NAME		R"(\HGRGY003.ttf)"			//フォントの名前
//############### マクロ定義 ##################
#define FONT_NAME		"HGS行書体"					//フォントの正式名称
#define DEFAULT_FONTSIZE	128						//デフォルトのフォントサイズ
#define FONTSIZE_MINI		48						//フォントサイズ（ミニ）
#define FONTSIZE_DRAW_RANKING	54					//ランキング描画の時のフォントサイズ

//################ マクロ定義 エラーメッセージ #################
#define FONT_ERROR_TITLE "FONT_ERROR"						//エラータイトル
#define FONT_ERROR_MSG	"フォントが読み込めませんでした"	//エラーメッセージ

//################ クラスの定義 ##################
class FONT {

private:
	std::vector<std::string> FilePath;				//パス
	std::vector<std::string> FileName;				//名前

	int LoadFontNow;		//読み込んだフォントの数

	bool Isload;			//読み込めた

public:

	FONT(const char *,const char *,const char *);		//コンストラクタ
	 
	~FONT();								//デストラクタ

	bool GetIsLoad();						//読み込めたか

	void SetSize(int);						//フォントサイズ設定

	void AddFont(const char *, const char *, const char *);	//フォント追加

	void ChengFont(int);					//フォント変更

};

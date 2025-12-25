//SAVEDATA.hpp
//セーブデータを管理するクラス

#pragma once

//################## ヘッダファイル読み込み ####################
#include "DATA.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <direct.h>

//################## マクロ定義 #######################
#define SAVEDATA_DIR	R"(C:\IAI_DATA)"		//セーブデータの保存ディレクトリ名

#define SAVEDATA_NAME	R"(\Savedata.csv)"		//セーブデータの名前


//テキスト関係
#define DRAW_DATA_TEXT_INDEX	"ランキング"					//ランキングのテキストタイトル
#define DRAW_DATA_TEXT			"%2d位:%d人抜き(%d/%d/%d)"		//ランキング描画のテキスト
#define DRAW_DATA_X		0	//ランキング描画開始X位置
#define DRAW_DATA_Y		0	//ランキング描画開始Y位置
#define DRAW_DATA_MAX	10	//描画するデータの数

//############## マクロ定義：エラーメッセージ ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//エラータイトル
#define DATA_ERROR_MSG		"データが読み込めませんでした"		//エラーメッセージ

//################## クラス定義 #######################
class SAVEDATA
{

private:

	std::vector<DATA*> DataCode;			//セーブデータ

public:

	SAVEDATA();		//コンストラクタ
	~SAVEDATA();	//デストラクタ

	void Add(int);	//データ追加

	bool Save();	//セーブ
	bool Load();	//読み込み

	void Sort();	//セーブデータを降順に並べ替える

	void Draw();	//データ描画


};

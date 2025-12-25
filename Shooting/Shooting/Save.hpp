//Save.hpp
//セーブ関係のクラス

#pragma once

//################# ヘッダファイル読み込み #################
#include "Global.hpp"
#include "Data.hpp"
#include <fstream>
#include <sys/stat.h>
#include <direct.h>

//################## マクロ定義 #######################
#define SAVEDATA_DIR	R"(C:\Syateki)"		//セーブデータの保存ディレクトリ名

#define SAVEDATA_NAME	R"(\Syateki.csv)"	//セーブデータの名前

#define SAVE_MAX		15	//保存するデータの最大数

//############## マクロ定義：エラーメッセージ ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//エラータイトル
#define DATA_ERROR_MSG		"データが読み込めませんでした"		//エラーメッセージ

using std::string;
using std::vector;

//########### クラス定義 #############
class Save
{

private:


public:

	Save();		//コンストラクタ
	~Save();	//デストラクタ

	static bool Load(vector<Data*>*);		//読み込み
	static bool DataSave(vector<Data*>);	//セーブ
	static void Sort(vector<Data*>*);		//ソート処理


};

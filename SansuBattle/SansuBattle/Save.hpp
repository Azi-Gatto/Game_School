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
#define SAVEDATA_DIR	R"(C:\SansuBattle)"		//セーブデータの保存ディレクトリ名

#define SAVE_NAME_SUM			R"(\Save_Add.csv)"			//セーブデータの名前(足し算)
#define SAVE_NAME_DIF			R"(\Save_Dif.csv)"			//セーブデータの名前(引き算)
#define SAVE_NAME_PRO			R"(\Save_Pro.csv)"			//セーブデータの名前(掛け算)
#define SAVE_NAME_DEA			R"(\Save_Dea.csv)"			//セーブデータの名前(割り算)
#define SAVE_NAME_SUM_DIF		R"(\Save_SumDif.csv)"		//セーブデータの名前(足し算、引き算)
#define SAVE_NAME_PRO_DEA		R"(\Save_ProDea.csv)"		//セーブデータの名前(掛け算、割り算)
#define SAVE_NAME_SUM_PRO		R"(\Save_SumPro.csv)"		//セーブデータの名前(+*)
#define SAVE_NAME_SUM_DEA		R"(\Save_SumDea.csv)"		//セーブデータの名前(+/)
#define SAVE_NAME_DIF_PRO		R"(\Save_DifPro.csv)"		//セーブデータの名前(-*)
#define SAVE_NAME_SUM_DIF_PRO	R"(\Save_SumDifPro.csv)"	//セーブデータの名前(+-*)
#define SAVE_NAME_SUM_DIF_DEA	R"(\Save_SumDifDea.csv)"	//セーブデータの名前(+-/)
#define SAVE_NAME_ALL			R"(\Save_All.csv)"			//セーブデータの名前(+-*/)

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

	static vector<string> NameTable;	//ファイル名のテーブル

	static void CreateTable();			//テーブルの作成

public:

	Save();		//コンストラクタ
	~Save();	//デストラクタ

	static bool Load(vector<Data*>*,int);		//読み込み
	static bool DataSave(vector<Data*>,int);	//セーブ
	static void Sort(vector<Data*>*);			//ソート処理


};

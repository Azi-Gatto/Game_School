//Data.hpp
//データを管理するクラス

#pragma once

//################### ヘッダファイル読み込み ###################
#include "Global.hpp"

//################### マクロ定義 #####################
#define RANKING_DRAW_Y	10	//ランキング描画Y位置

//#define RANK_INDEX_TEXT	"ランキング"	//表題テキスト

//テキスト関係
#define TXT_MD_SUM			"たしざん"						//足し算モードのテキスト
#define TXT_MD_DIF			"ひきざん"						//引き算モードのテキスト
#define TXT_MD_PRO			"かけざん"						//掛け算モードのテキスト
#define TXT_MD_DEA			"わりざん"						//割り算モードのテキスト
#define TXT_MD_SUM_DIF		"たしざん、ひきざん"			//足し算と引き算モードのテキスト
#define TXT_MD_PRO_DEA		"かけざん、わりざん"			//掛け算と割り算モードのテキスト
#define TXT_MD_SUM_PRO		"たしざん、かけざん"			//+*モードのテキスト
#define TXT_MD_SUM_DEA		"たしざん、わりざん"			//+/モードのテキスト
#define TXT_MD_DIF_PRO		"ひきざん、かけざん"			//-*モードのテキスト
#define TXT_MD_SUM_DIF_PRO	"たしざん、ひきざん、かけざん"	//+-*モードのテキスト
#define TXT_MD_SUM_DIF_DEA	"たしざん、ひきざん、わりざん"	//+-/モードのテキスト
#define TXT_MD_ALL			"まとめ"						//allモードのテキスト

#define DRAW_DATA_TEXT	"%2d:%dpt(%d/%d/%d)"				//ランキング描画のテキスト
#define DRAW_DATA_X		20	//ランキング描画開始X位置
#define DRAW_DATA_Y		20	//ランキング描画開始Y位置

#define RANKING_DRAW_MAX 10	//描画するデータの最大数

using std::string;

//################### クラス定義 #####################
class Data
{

private:

	int Score;		//スコア
	int Element;	//要素番号
	static int ElementCnt;	//要素数
	static vector<string> TxtTable;	//テキストテーブル

	DATEDATA date;	//日付データ


public:

	Data(DATEDATA,int);	//コンストラクタ
	Data(int);			//コンストラクタ
	~Data();			//デストラクタ

	void SetDate(DATEDATA);	//日付データ設定
	void SetScore(int);		//スコア設定

	DATEDATA GetDate();	//日付データ取得
	int GetScore();		//スコア取得

	void Draw(int);			//スコア描画
	void SetElement(int);	//要素番号設定
	int GetElement();		//要素番号取得
	static void CntClear();	//カウントをクリアする

};

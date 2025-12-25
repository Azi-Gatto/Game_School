//Data.cpp
//データを管理するクラス

//################# ヘッダファイル読み込み ##################
#include "Data.hpp"

//################# クラス定義 ###################

int Data::ElementCnt = 0;	//要素数
//テキストテーブル
vector<string> Data::TxtTable = { TXT_MD_SUM,			//足し算モードのテキスト
								  TXT_MD_DIF,			//引き算モードのテキスト
								  TXT_MD_PRO,			//掛け算モードのテキスト
								  TXT_MD_DEA,			//割り算モードのテキスト
								  TXT_MD_SUM_DIF,		//足し算と引き算モードのテキスト
								  TXT_MD_PRO_DEA,		//掛け算と割り算モードのテキスト
								  TXT_MD_SUM_PRO,		//+*モードのテキスト
								  TXT_MD_SUM_DEA,		//+/モードのテキスト
								  TXT_MD_DIF_PRO,		//-*モードのテキスト
								  TXT_MD_SUM_DIF_PRO,	//+-*モードのテキスト
								  TXT_MD_SUM_DIF_DEA,	//+-/モードのテキスト
								  TXT_MD_ALL };			//allモードのテキスト

//コンストラクタ
Data::Data(DATEDATA date, int score)
{
	//メンバー初期化
	this->date = date;	//データ
	Score = score;		//スコア
	Element = ElementCnt++;	//要素番号
}

//コンストラクタ
Data::Data(int score)
{
	//メンバー初期化
	date = { 0 };			//データ
	GetDateTime(&date);		//データ取得
	Score = score;			//スコア
	Element = ElementCnt++;	//要素番号
}

//デストラクタ
Data::~Data() {}

//日付データ設定
void Data::SetDate(DATEDATA date)
{
	this->date = date;
}

//スコア設定
void Data::SetScore(int score)
{
	Score = score;
}

//日付データ取得
DATEDATA Data::GetDate()
{
	return date;
}

//スコア取得
int Data::GetScore()
{
	return Score;
}

//スコア描画
void Data::Draw(int mode)
{
	if (Element >= RANKING_DRAW_MAX)	//描画する最大数より多ければ
		return;	//描画せず終了

	int height = GetFontSizeToHandle(Font::GetNowHandle());	//高さ取得

	string text_gamemode = TxtTable.at(mode);	//ゲームモード毎のテキストを取得

	DrawStringToHandle(DRAW_DATA_X, DRAW_DATA_Y, text_gamemode.c_str(), COLOR_WHITE, Font::GetNowHandle());		//ランキングタイトル描画

	DrawFormatStringToHandle(DRAW_DATA_X, DRAW_DATA_Y + (Element + 1) * height, COLOR_WHITE, Font::GetNowHandle(), DRAW_DATA_TEXT,
		Element + 1,//何位か
		Score,		//スコア
		date.Year,	//年
		date.Mon,	//月
		date.Day);	//日

}

//要素番号設定
void Data::SetElement(int element)
{
	Element = element;
}

//要素番号取得
int Data::GetElement()
{
	return Element;
}

//カウントをクリアする
void Data::CntClear()
{
	ElementCnt = 0;
}

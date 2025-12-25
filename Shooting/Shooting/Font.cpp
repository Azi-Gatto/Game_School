//Font.cpp
//フォントクラス

//############### ヘッダファイル読み込み ####################
#include "Font.hpp"

//############### クラスの定義 #####################

//インスタンス背性
vector<string> Font::LoadFontName;	//読み込んだフォントの名前
vector<string> Font::FilePath;		//読み込んだフォントのパス
int Font::NowFont;					//現在のフォントハンドル

//コンストラクタ
//引数は、DxLibのCreateFontToHandle()の引数と同じ
//引　数：int：読み込むフォントの名前
//引　数：int：フォントのサイズ
//引　数：int：フォントの太さ
//引　数：int：フォントのタイプ
//残りの引数は、デフォルト引数
Font::Font(int fontname, int size, int bold, int fonttype, int charset,
	int edgesize,
	int ltalic,
	int handle)
{
	//メンバー初期化
	Handle = -1;		//ハンドル初期化
	IsCreate = false;	//作成できたか

	if (LoadFontName.empty())	//フォントを読み込んでいなければ
	{
		//フォントの読み込みを行う
		IsCreate = LoadFont(FONT_DIR, FONT_FILE_NAME, FONT_NAME);
		if (!IsCreate)		//読み込めていなければ
			return;			//読み込み失敗
	}

	Handle = CreateFontToHandle(LoadFontName.at(fontname).c_str(), size, bold, fonttype,charset,edgesize,ltalic,handle);	//フォントハンドルを作成

	//ハンドルの作成に成功したかどうか
	Handle == -1 ? IsCreate = false : IsCreate = true;


}

//デストラクタ	
Font::~Font(){}

//フォントを読み込み
bool Font::LoadFont(const char* dir, const char* name, const char* fontname)
{
	string LoadFilePath = dir;
	LoadFilePath += name;

	//フォント読み込み
	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) <= 0)		//読み込み失敗
	{
		string ErroeMsg(FONT_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');				//改行
		ErroeMsg += LoadFilePath;			//フォントのパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(FONT_ERROR_TITLE),
			MB_OK);

		return false;	//読み込み失敗

	}

	LoadFontName.push_back(fontname);	//読み込んだフォントの名前を追加
	FilePath.push_back(LoadFilePath);	//読み込んだフォントのパスを追加

	return true;

}

//読み込んだフォントを開放
bool Font::ReleaseFont()
{
	for (int i = 0; i < LoadFontName.size(); ++i)
	{
		if (RemoveFontResourceEx(FilePath.at(i).c_str(), FR_PRIVATE, NULL) == 0)	//失敗時
		{
			MessageBox(NULL, "remove failure", "", MB_OK);				//エラーメッセージ
			return false;
		}

	}
	return true;
}

//作成できたか取得
bool Font::GetIsCreate()
{
	return IsCreate;
}

//フォントハンドルを変更
void Font::Chenge()
{
	NowFont = Handle;
}

//現在のハンドルを取得
int Font::GetNowHandle()
{
	return NowFont;
}

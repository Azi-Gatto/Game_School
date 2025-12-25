//FONT.cpp
//フォントクラス

//############### ヘッダファイル読み込み ####################
#include "FONT.hpp"

//############### クラスの定義 #####################

//コンストラクタ
//引　数：const char *：フォントのディレクトリ
//引　数：const char *：フォントの名前
//引　数：const char *：フォントの正式名称
FONT::FONT(const char *dir,const char *filename,const char *name)
{
	//メンバー変数初期化
	this->FileName.resize(FONT_KIND);
	this->FilePath.resize(FONT_KIND);
	this->Path_itr = this->FilePath.begin();	//先頭要素
	this->Name_itr = this->FileName.begin();	//先頭要素
	this->LoadFontNow = 0;	//読み込んだフォントの数0
								
	//フォントを読み込み
	std::string LoadFilePath;		//フォントのパスを作成

	LoadFilePath += dir;
	LoadFilePath += filename;
	
	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) <= 0)		//読み込み失敗
	{
		std::string ErroeMsg(FONT_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadFilePath;				//フォントのパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(FONT_ERROR_TITLE),
			MB_OK);

		return;

	}


	ChangeFont(name, DX_CHARSET_DEFAULT);							//指定されたフォントに変更
	this->SetSize(DEFAULT_FONTSIZE);								//フォントサイズをデフォルトの数字に設定

	*this->Path_itr = LoadFilePath;			//先頭要素へ代入
	*this->Name_itr = name;					//先頭要素へ代入

	this->Isload = true;		//読み込めた
	this->LoadFontNow++;		//読み込んだフォントの数を追加

	return;

}

FONT::FONT()
{
	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->FilePath.swap(v);					//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<std::string> v2;			//空のvectorを作成する
	this->FileName.swap(v2);				//空と中身を入れ替える


	return;
}

//デストラクタ	
FONT::~FONT()
{
	for (int i = 0; i < this->LoadFontNow; ++i)
	{
		if (RemoveFontResourceEx(this->FilePath[i].c_str(), FR_PRIVATE, NULL) == 0)	//失敗時
		{

			MessageBox(NULL, "remove failure", "", MB_OK);				//エラーメッセージ

		}
	}
}

//読み込めたか
bool FONT::GetIsLoad()
{
	return this->Isload;
}

//フォントサイズ設定
void FONT::SetSize(int size)
{

	SetFontSize(size);

	return;
}

//フォント追加
//引　数：const char *：フォントのディレクトリ
//引　数：const char *：フォントの名前
//引　数：const char *：フォントの正式名称
void FONT::AddFont(const char *dir, const char *filename, const char *name)
{

	this->Isload = false;	//読み込んでない

	this->Name_itr++;	//格納する位置を次の要素へ
	this->Path_itr++;	//格納する位置を次の要素へ

	//フォントを読み込み
	std::string LoadFilePath;		//フォントのパスを作成

	LoadFilePath += dir;
	LoadFilePath += filename;

	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) <= 0)		//読み込み失敗
	{
		std::string ErroeMsg(FONT_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadFilePath;				//フォントのパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(FONT_ERROR_TITLE),
			MB_OK);

		return;

	}

	*this->Path_itr = LoadFilePath;			//代入
	*this->Name_itr = name;					//代入

	this->Isload = true;		//読み込めた
	this->LoadFontNow++;		//読み込んだフォントの数を追加

	return;
}

//フォント変更
void FONT::ChengFont(int fontType)
{
	ChangeFont(this->FileName[fontType].c_str(), DX_CHARSET_DEFAULT);			//指定されたフォントに変更
	return;
}

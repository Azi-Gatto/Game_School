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
	this->LoadFontNow = 0;		//読み込んだフォントの数0
								
	//フォントを読み込み
	std::string LoadFilePath;	//フォントのパスを作成

	LoadFilePath += dir;
	LoadFilePath += filename;
	
	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) == 0)		//読み込み失敗
	{
		std::string ErroeMsg(FONT_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadFilePath;				//フォントのパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(FONT_ERROR_TITLE),
			MB_OK);

		this->Isload = false;		//読み込み失敗

		return;

	}

	this->FilePath.push_back(LoadFilePath.c_str());
	this->FileName.push_back(name);

	ChangeFont(name);							//指定されたフォントに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	//フォントのタイプをアンチエイリアスフォントに変更
	this->SetSize(DEFAULT_FONTSIZE);	//フォントサイズをデフォルトの数字に設定

	this->Isload = true;		//読み込めた
	++this->LoadFontNow;		//読み込んだフォントの数を追加

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

	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->FilePath.swap(v);					//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<std::string> v2;			//空のvectorを作成する
	this->FileName.swap(v2);				//空と中身を入れ替える

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

		this->Isload = false;		//読み込み失敗

		return;

	}

	this->FilePath.push_back(LoadFilePath.c_str());
	this->FileName.push_back(name);

	this->Isload = true;		//読み込めた
	++this->LoadFontNow;		//読み込んだフォントの数を追加

	return;
}

//フォント変更
void FONT::ChengFont(int fontType)
{
	ChangeFont(this->FileName[fontType].c_str());			//指定されたフォントに変更
	return;
}

//MGCLIST.cpp
//魔法リストのクラス

//################ ヘッダファイル読み込み #################
#include "LIST_MGC.hpp"

//################ クラス定義 ####################

//コンストラクタ
/*
引数：const char *：読み込むデータのディレクトリ
引数：const char *：読み込むデータの名前
*/
LIST_MGC::LIST_MGC(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(LIST_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(LIST_ERROR_TTILE),
			MB_OK);

		this->SetIsLoad(false);	//読み込み失敗

		return;	//読み込み失敗

	}


	std::string buf;

	//1行目を読み込んで飛ばす
	std::getline(ifs, buf);	//1行読み込み

	while (!ifs.eof())		//ファイル終端まで読み込み
	{

		std::getline(ifs, buf, ',');				//カンマまで読み込み
		this->SetCode(atoi(buf.c_str()));		//コード番号読み込み

		std::getline(ifs, buf, ',');				//カンマまで読み込み
		this->SetName(buf.c_str());					//名前読み込み

		std::getline(ifs, buf, '\n');				//改行まで読み込み
		this->Cost.push_back(atoi(buf.c_str()));	//消費MP読み込み


	}

	this->SetSize();		//リストの要素数設定

	this->SetIsLoad(true);	//読み込み成功

	return;

}

//デストラクタ
LIST_MGC::~LIST_MGC()
{
	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Cost.swap(v);			//空と中身を入れ替える
}

//消費MP取得
int LIST_MGC::GetCost(int kind)
{
	return this->Cost[kind];
}

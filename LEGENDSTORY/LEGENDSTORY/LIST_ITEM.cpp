//LIST_ITEM.cppクラス
//LISTクラスの派生
//アイテムの一覧を管理するクラス

//################# ヘッダファイル読み込み ##############
#include "LIST_ITEM.hpp"

//################# クラス定義 ######################

//コンストラクタ
/*
引数：const char *：読み込むデータのディレクトリ
引数：const char *：読み込むデータの名前
*/
LIST_ITEM::LIST_ITEM(const char *dir, const char *name)
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


	std::string buf;		//ファイル読み込み用

	//1行目を読み込んで飛ばす
	std::getline(ifs, buf);	//1行読み込み

	int cnt = 0;	//ループ数カウント用
	int type_key_pos = 0;	//アイテムタイプのキーとなる場所の位置を入れる変数

	while (!ifs.eof())		//ファイル終端まで読み込み
	{

		std::getline(ifs, buf, ',');				//カンマまで読み込み
		this->SetCode(atoi(buf.c_str()));		//コード番号読み込み

		std::getline(ifs, buf, ',');				//カンマまで読み込み
		this->SetName(buf.c_str());					//名前読み込み

		std::getline(ifs, buf, ',');					//カンマまで読み込み
		this->Recovery.push_back(atoi(buf.c_str()));	//回復量読み込み

		std::getline(ifs, buf, '\n');				//改行まで読み込み
		this->Description.push_back(buf.c_str());	//説明文読み込み

		type_key_pos = this->Description[cnt].find(TYPE_HP_KEY);	//HPという単語を探し、先頭の位置を取得する
		if (type_key_pos == -1)	//HPという単語が見つからなかったら
		{
			type_key_pos = this->Description[cnt].find(TYPE_MP_KEY);	//MPという単語を探し、先頭の位置を取得する
		}

		this->Type.push_back(this->Description[cnt][type_key_pos]);	//単語の先頭文字を、アイテムタイプとして格納する

		++cnt;	//カウントアップ

	}

	this->SetSize();		//リストの要素数設定

	this->SetIsLoad(true);	//読み込み成功

	return;

}

//デストラクタ
LIST_ITEM::~LIST_ITEM()
{
	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Recovery.swap(v);		//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<std::string> v2;	//空のvectorを作成する
	this->Description.swap(v2);		//空と中身を入れ替える

	return;

}

//回復量取得
int LIST_ITEM::GetRecovery(int code)
{
	for (int i = 0; i < this->GetListSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			return this->Recovery[i];
		}
	}
}

//説明文取得
const char * LIST_ITEM::GetDescription(int code)
{

	for (int i = 0; i < this->GetListSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			return this->Description[i].c_str();
		}
	}

}

//アイテムのタイプを取得
char LIST_ITEM::GetItemType(int code)
{
	for (int i = 0; i < this->GetListSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			return this->Type[i];
		}
	}

}

//Save.cpp
//セーブ関係のクラス

//################## ヘッダファイル読み込み ####################
#include "Save.hpp"

//################### クラス定義 ######################

vector<string> Save::NameTable;	//ファイル名のテーブル

//コンストラクタ
Save::Save(){}

//デストラクタ 
Save::~Save(){}

//読み込み
bool Save::Load(vector<Data*> *data, int mode)
{

	CreateTable();	//テーブルの作成

	if (!data->empty())	//空じゃなければ
	{
		data->clear();		//データリセット
		Data::CntClear();	//カウントをクリア
	}

	struct stat statbuf;			//ファイルの存在確認に使用
	string LoadFile;
	LoadFile += SAVEDATA_DIR;
	LoadFile += NameTable.at(mode);
	if (stat(LoadFile.c_str(), &statbuf) == 0)		//セーブデータ用のファイルが作成されている場合
	{

		std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

		if (!ifs)		//ファイルオープン失敗時
		{
			string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
			ErrorMsg += TEXT('\n');				//改行
			ErrorMsg += LoadFile;				//画像のパス

			MessageBox(
				NULL,
				ErrorMsg.c_str(),	//char * を返す
				TEXT(DATA_ERROR_TTILE),
				MB_OK);

			return false;	//読み込み失敗

		}

		string buf;
		int sc = 0;		//スコア
		int cnt = 0;	//カウント用
		DATEDATA date;	//日付データ

		while (!ifs.eof())				//最後の行まで読み込み
		{
			std::getline(ifs, buf, ',');	//カンマまで読み込み
			date.Year = atoi(buf.c_str());	//年読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			date.Mon = atoi(buf.c_str());	//月読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			date.Day = atoi(buf.c_str());	//日読み込み

			std::getline(ifs, buf, '\n');	//改行まで読み込み
			sc = atoi(buf.c_str());			//スコア読み込み


			data->push_back(new Data(date, sc));		//データ追加
		}

	}

	return true;	//読み込み成功
}

//セーブ
bool Save::DataSave(vector<Data*> data, int mode)
{

	CreateTable();	//テーブルの作成

	struct stat statbuf;			//ファイルの存在確認に使用
	if (stat(SAVEDATA_DIR, &statbuf) != 0)		//セーブデータ用のファイルが作成されていない場合
	{
		_mkdir(SAVEDATA_DIR);	//セーブデータを格納するフォルダを作成
	}

	string LoadFile;
	LoadFile += SAVEDATA_DIR;
	LoadFile += NameTable.at(mode);

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//ファイルオープン

	if (!ofs)		//ファイルオープン失敗時
	{
		string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;		//セーブ失敗

	}

	vector<DATEDATA> date;	//日付データ
	vector<int>	score;		//スコア
	for (auto d : data)
	{
		date.push_back(d->GetDate());	//日付データをコピー
		score.push_back(d->GetScore());	//スコアをコピー
	}

	//セーブデータを書き込む
	for (int i = 0; i < SAVE_MAX; ++i)	//保存する最大数までループ
	{

		if (i >= data.size())	//データの個数に達したら
			break;

		ofs << date.at(i).Year << ',';	//年、書き出し
		ofs << date.at(i).Mon << ',';	//月、書き出し
		ofs << date.at(i).Day << ',';	//日、書き出し
		ofs << score.at(i);				//スコア書き出し

		//最後の書き込みなら終端文字を付け、そうじゃなければ改行
		i == data.size() - 1 ? ofs << '\0' : ofs << '\n';

	}

	//vectorの解放
	vector<DATEDATA> v;	
	date.swap(v);
	vector<int>	v2;
	score.swap(v2);

	return true;	//セーブ成功
}

//ソート処理
void Save::Sort(vector<Data*> *data)
{
	for (int i = 0; i < data->size(); ++i)
	{
		for (int j = data->size() - 1; j > i; --j)
		{
			if (data->at(j)->GetScore() > data->at(j - 1)->GetScore())
			{
				auto temp = data->at(j);
				data->at(j) = data->at(j - 1);
				data->at(j - 1) = temp;
				//要素番号の交換
				auto temp2 = data->at(j)->GetElement();
				data->at(j)->SetElement(data->at(j - 1)->GetElement());
				data->at(j - 1)->SetElement(temp2);
			}
		}
	}
}

//テーブルの作成
void Save::CreateTable()
{
	if (NameTable.empty())	//テーブルが作成されていなければ
	{
		//ファイル名のテーブルを作成
		NameTable = { SAVE_NAME_SUM ,	//足し算
			SAVE_NAME_DIF,				//引き算
			SAVE_NAME_PRO,				//掛け算
			SAVE_NAME_DEA,				//割り算
			SAVE_NAME_SUM_DIF,			//+-
			SAVE_NAME_PRO_DEA,			//*/
			SAVE_NAME_SUM_PRO,			//+*
			SAVE_NAME_SUM_DEA,			//+/
			SAVE_NAME_DIF_PRO,			// /*
			SAVE_NAME_SUM_DIF_PRO,		//+-*
			SAVE_NAME_SUM_DIF_DEA,		//+-/
			SAVE_NAME_ALL				//+-*/
		};
	}
}

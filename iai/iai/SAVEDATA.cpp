//SAVEDATA.cpp
//セーブデータを管理するクラス

//################### ヘッダファイル読み込み ##################
#include "SAVEDATA.hpp"

//#################### クラス定義 #######################

//コンストラクタ
SAVEDATA::SAVEDATA()
{
	return;
}

//デストラクタ
SAVEDATA::~SAVEDATA()
{

	for (int i = 0; i < this->DataCode.size(); ++i)
	{
		delete this->DataCode.at(i);
	}

	//vectorのメモリ解放を行う
	std::vector<DATA*> v;			//空のvectorを作成する
	this->DataCode.swap(v);			//空と中身を入れ替える


	return;
}

//データ追加
void SAVEDATA::Add(int win_num)
{

	DATEDATA Date;		//現在時刻

	GetDateTime(&Date);	//現在時刻取得

	this->DataCode.push_back(new DATA(Date.Year,Date.Mon,Date.Day,win_num));	//データ情報追加

	return;

}

//セーブ
bool SAVEDATA::Save()
{

	struct stat statbuf;	//ディレクトリの存在確認に使用

	if (stat(SAVEDATA_DIR, &statbuf) != 0)//セーブデータ用のフォルダが作成されていない場合（初めてのセーブの場合）
	{
		_mkdir(SAVEDATA_DIR);	//セーブデータを格納するフォルダを作成
	}

	std::string LoadFile;
	LoadFile += SAVEDATA_DIR;
	LoadFile += SAVEDATA_NAME;

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//ファイルオープン

	if (!ofs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;		//セーブ失敗

	}

	//セーブデータを書き込む
	for (int i = 0; i < this->DataCode.size(); ++i)	//データの数だけループ
	{
		ofs << this->DataCode.at(i)->GetYear() << ',';				//年、書き出し
		ofs << this->DataCode.at(i)->GetMonth() << ',';				//月、書き出し
		ofs << this->DataCode.at(i)->GetDay() << ',';				//日、書き出し
		if (i == this->DataCode.size() - 1)	//最後の書き込みだったら
		{
			//終端文字を付ける
			ofs << this->DataCode.at(i)->GetWinNum() << '\0';			//勝ち数、書き出し
		}
		else	//最後の書き込みじゃなければ
		{
			//改行する
			ofs << this->DataCode.at(i)->GetWinNum() << '\n';			//勝ち数、書き出し
		}


	}

	return true;		//セーブ成功
}

//読み込み
bool SAVEDATA::Load()
{
	std::string LoadFile;
	LoadFile += SAVEDATA_DIR;
	LoadFile += SAVEDATA_NAME;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}


	std::string buf;
	int yy = 0, mm = 0, dd = 0, wn = 0;		//年、月、日、勝ち数

	while (!ifs.eof())				//最後の行まで読み込み
	{
		std::getline(ifs, buf,',');		//カンマまで読み込み
		yy = atoi(buf.c_str());			//年読み込み
		
		std::getline(ifs, buf, ',');	//カンマまで読み込み
		mm = atoi(buf.c_str());			//月読み込み

		std::getline(ifs, buf, ',');	//カンマまで読み込み
		dd = atoi(buf.c_str());			//日読み込み

		std::getline(ifs, buf, '\n');	//改行まで読み込み
		wn = atoi(buf.c_str());			//勝ち数読み込み

		this->DataCode.push_back(new DATA(yy, mm, dd, wn));		//データ追加

	}

	return true;	//読み込み成功
}

//**************** ソート関係 ******************
//セーブデータを降順に並べ替える
void SAVEDATA::Sort()
{

	for (int i = 0; i < this->DataCode.size(); ++i)
	{
		for (int j = this->DataCode.size() - 1; j > i; --j)
		{
			if (this->DataCode.at(j)->GetWinNum() > this->DataCode.at(j - 1)->GetWinNum())
			{
				auto temp = this->DataCode.at(j);
				this->DataCode.at(j) = this->DataCode.at(j - 1);
				this->DataCode.at(j - 1) = temp;
			}
		}
	}

	return;
}

//データ描画
void SAVEDATA::Draw()
{

	int Height = GetFontSize();		//高さ取得

	DrawString(DRAW_DATA_X, DRAW_DATA_Y, DRAW_DATA_TEXT_INDEX, GetColor(255, 255, 255));		//ランキングタイトル描画

	for (int i = 0; i < this->DataCode.size();++i)
	{

		if (i >= DRAW_DATA_MAX)		//ランキング描画する最大数になったら
		{
			break;					//ループを抜ける
		}

		DrawFormatString(DRAW_DATA_X, DRAW_DATA_Y + (i + 1) * Height, GetColor(255, 255, 255), DRAW_DATA_TEXT,
			i + 1,								//何位か
			this->DataCode.at(i)->GetWinNum(),	//勝ち数
			this->DataCode.at(i)->GetYear(),	//年
			this->DataCode.at(i)->GetMonth(),	//月
			this->DataCode.at(i)->GetDay());	//日
	}

	return;
}

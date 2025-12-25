//NPC.cpp
//NPCを管理するクラス

//################### ヘッダファイル読み込み #######################
#include "NPC.hpp"

//################### クラス定義 ####################

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
NPC::NPC(const char *dir, const char *name)
{
	this->ImageIsLoad = false;	//読み込めたか初期化

	this->Image = new IMAGE(dir, name);				//NPC画像の生成（読み込み）
	this->ImageIsLoad = this->Image->GetIsLoad();	//読み込めたか設定

	return;

}

//デストラクタ
NPC::~NPC()
{
	delete this->Image;		//Image破棄

	//vectorのメモリ解放を行う
	std::vector<std::string> v;		//空のvectorを作成する
	this->Name.swap(v);				//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<int> v2;			//空のvectorを作成する
	this->DrawMapKind.swap(v2);		//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<int> v3;			//空のvectorを作成する
	this->Draw_X.swap(v3);			//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<int> v4;			//空のvectorを作成する
	this->Draw_X.swap(v4);			//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<int> v5;			//空のvectorを作成する
	this->Draw_Y.swap(v5);			//空と中身を入れ替える

	return;

}

//画像を読み込めたか取得
bool NPC::GetImageIsLoad(void)
{
	return this->ImageIsLoad;
}

//NPCを描画する
void NPC::DrawNPC(int drawmap_kind,int drawmap_num)
{

	for (int i = 0; i < this->DrawMapKind.size(); ++i)	//NPCの数分
	{
		if (drawmap_kind == this->DrawMapKind[i] &&		//描画するマップの種類が一緒で、
			drawmap_num == this->DrawMap_Num[i])		//描画するマップ番号が一緒だった場合
		{
			this->Image->Draw(this->Draw_X[i], this->Draw_Y[i], i);	//NPC描画
		}
	}

	return;
}

//NPCデータを読み込む
//引　数：const char *：データのディレクトリ
//引　数：const char *：データの名前
bool NPC::Load(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(NPC_DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;						//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(NPC_DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}

	std::string buf;
	//1行目を読み込んで飛ばす
	std::getline(ifs, buf);	//1行読み込み

	while (!ifs.eof())	//最後の行まで読み込み
	{

		std::getline(ifs, buf, ',');						//カンマまで読み込み

		if (buf.empty())	//読み取った内容が空だったら
		{
			break;	//読み取り処理終了
		}

		this->Name.push_back(buf.c_str());					//名前設定

		std::getline(ifs, buf, ',');						//カンマまで読み込み
		this->DrawMapKind.push_back(atoi(buf.c_str()));		//描画マップの種類を設定

		std::getline(ifs, buf, ',');						//カンマまで読み込み
		this->DrawMap_Num.push_back(atoi(buf.c_str()));		//描画マップ番号を設定

		std::getline(ifs, buf, ',');						//カンマまで読み込み
		this->Draw_X.push_back(atoi(buf.c_str()));			//描画X位置を設定

		std::getline(ifs, buf, '\n');						//最後は改行まで読み込み
		this->Draw_Y.push_back(atoi(buf.c_str()));			//描画Y位置を設定

	}

	return true;

}

//NPCの画像を追加する
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
bool NPC::AddImage(const char *dir, const char*name)
{
	return this->Image->AddImage(dir, name);	//画像を追加
}

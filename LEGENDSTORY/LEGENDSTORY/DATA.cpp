//DATA.cpp
//データクラス

//#################### ヘッダファイル読み込み #################
#include "DATA.hpp"

//#################### クラス定義 #########################

//コンストラクタ

DATA::DATA()
{
	return;
}

//デストラクタ
DATA::~DATA()
{
	return;
}

//読み込み（敵データ）
bool DATA::LoadEnemy(ENEMY *enemy[],const char *dir,const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;
	
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
	//1行目を読み込んで飛ばす
	std::getline(ifs, buf);	//1行読み込み

		for (int i = 0; i < ENEMY_KIND; ++i)				//敵の種類分読み込み
		{
			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetName(buf.c_str());	//名前読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetMaxHP(atoi(buf.c_str()));	//HP読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetATK(atoi(buf.c_str()));	//ATK読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetDEF(atoi(buf.c_str()));	//DEF読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetSPD(atoi(buf.c_str()));	//SPD読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetEXP(atoi(buf.c_str()));	//EXP読み込み
			
			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetSkil(atoi(buf.c_str()));	//Skil1読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetSkil(atoi(buf.c_str()));	//Skil2読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetEncounteRate(atoi(buf.c_str()));	//遭遇率読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetEmergenceMap(atoi(buf.c_str()));	//出現MAP読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetItemCode(atoi(buf.c_str()));	//ドロップするアイテムコード読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetWeaponCode(atoi(buf.c_str()));	//ドロップする武器コード読み込み

			std::getline(ifs, buf, '\n');	//最後は改行まで読み込み
			enemy[i]->SetArmorCode(atoi(buf.c_str()));	//ドロップする防具コード読み込み

		}

		return true;	//読み込み成功

}

//読み込み（メッセージデータ）
bool DATA::LoadMsg(MESSAGE *msg, const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

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

		std::getline(ifs, buf);					//1行読み込み
		msg->SetMsg(buf.c_str());				//文字列読み込み

		while (!ifs.eof())	//最後の行まで読み込み
		{
			std::getline(ifs, buf);	//1行読み込み
			msg->AddMsg(buf.c_str());	//文字列追加
		}

		return true;	//読み込み成功

}

//読み込み（現在のマップ位置）
bool DATA::LoadNowMap(int *nowmapdrawkind, int *nowmapkind, const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

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

	std::getline(ifs, buf, ',');			//カンマまで読み込み
	*nowmapdrawkind = atoi(buf.c_str());	//現在の描画マップの種類

	std::getline(ifs, buf, ',');			//改行まで読み込み
	nowmapkind[0] = atoi(buf.c_str());		//現在のマップの種類
	std::getline(ifs, buf, '\n');			//改行まで読み込み
	nowmapkind[1] = atoi(buf.c_str());		//現在のマップの種類

	return true;			//読み込み成功

}

//現在のマップ位置をセーブ
bool DATA::SaveMap(int nowmapdrawkind, int nowmapkind[],const char *dir,const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

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

	//現在のマップ位置を書き出す
	ofs << nowmapdrawkind << ',';		//現在の描画マップの種類
	ofs << nowmapkind[0] << ',' ;		//現在のマップの種類
	ofs << nowmapkind[1] << std::endl;

	return true;		//セーブ成功

}

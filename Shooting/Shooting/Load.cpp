//Load.cpp
//ロード画面のクラス

//############## ヘッダファイル読み込み #################
#include "Load.hpp"

//############## クラス定義 ################

//コンストラクタ
Load::Load()
{
	//メンバー初期化
	IsGameStart = false;	//ゲームスタートできるか
}

//デストラクタ
Load::~Load(){}

//初期設定
void Load::SetInit(){}

//データ読込
bool Load::DataLoad()
{
	if (!Save::Load(&data)) { return false; }	//セーブデータ読み込み失敗
	font.push_back(new Font(F_NAME_HGS, F_SIZE_NORMAL, F_BOLD_NORMAL, DX_FONTTYPE_ANTIALIASING));	//フォント(通常サイズ生成)
	font.push_back(new Font(F_NAME_HGS, F_SIZE_MINI, F_BOLD_NORMAL, DX_FONTTYPE_ANTIALIASING));		//フォント(ミニサイズ生成)
	font.push_back(new Font(F_NAME_HGS, F_SIZE_RANKING, F_BOLD_NORMAL, DX_FONTTYPE_ANTIALIASING_EDGE_4X4,-1,F_EDGE_SIZE));	//フォント(ランキング用サイズ生成)
	for (auto f : font)
	{
		if (!f->GetIsCreate()) { return false; }	//読み込み失敗
	}
	font.at(FH_NORMAL)->Chenge();	//通常サイズのフォントに変更
	return true;
}

//読み込み画面の処理
void Load::Run()
{
	//***************************** 処理系 ************************************
	if (IsGameStart)	//ゲームスタートできるなら
	{
		if (Mouse::OnLeftClick())	//左クリックされたら
		{
			NowScene = SCENE_TITLE;	//タイトル画面へ
		}

	}

	if (GetASyncLoadNum() == 0)	//非同期で読み込んでいる処理が終わったら
	{

		SetUseASyncLoadFlag(FALSE);	//同期読み込みに設定

		IsGameStart = true;		//ゲームスタートできる
	}

	//********************************* 描画系 ************************************
	font.at(FH_MINI)->Chenge();	//フォント変更
	DrawStringToHandle(TEXT_DISCRIPTION_X, TEXT_DISCRIPTION_Y, TEXT_DISCRIPTION, GetColor(255, 255, 255), Font::GetNowHandle());
	font.at(FH_NORMAL)->Chenge();	//フォント変更

}

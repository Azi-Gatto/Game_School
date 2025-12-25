//End.cpp
//エンド画面の処理

//############# ヘッダファイル読み込み ###############
#include "Ranking.hpp"

//############# クラス定義 ################

//コンストラクタ
Ranking::Ranking()
{
	
}

//デストラクタ
Ranking::~Ranking()
{

}

//データ読込
bool Ranking::DataLoad()
{
	//画像関係
	if (!back->Load(IMG_DIR_BACK, IMG_NAME_RANKING)) { return false; }	//背景画像読み込み

	if (!bgm->Load(MUSIC_DIR_BGM, BGM_NAME_RANKING)) { return false; }	//BGM読み込み
	return true;
}

//初期設定
void Ranking::SetInit()
{
	back->SetInit();	//背景画像初期設定
	bgm->SetInit(DX_PLAYTYPE_LOOP, 30);		//BGM初期設定

}


//エンド画面の処理
void Ranking::Run()
{
	//************************** 処理系 *********************************
	bgm->Play();	//BGMを流す
	if (Mouse::OnLeftClick())	//左クリックされたら
	{
		bgm->Stop();			//BGMを止める
		NowScene = SCENE_TITLE;	//タイトル画面へ
	}


	//**************************** 描画系 *******************************
	back->Draw(GAME_LEFT, GAME_TOP);//背景描画
	font.at(FH_RANKING)->Chenge();	//フォントハンドル変更
	for (auto d : data)
	{
		d->Draw();	//スコア描画
	}
	font.at(FH_NORMAL)->Chenge();	//フォントハンドル変更

}
//Ranking.cpp
//ランキング画面の処理

//############# ヘッダファイル読み込み ###############
#include "Ranking.hpp"

//############# クラス定義 ################

//コンストラクタ
Ranking::Ranking()
{
	//画像関係
	if (!back->Load(IMG_DIR_BACK, IMG_NAME_RANKING)) { IsLoad = false; return; }	//背景画像読み込み

	if (!bgm.front()->Load(MUSIC_DIR_BGM, BGM_NAME_RANKING)) { IsLoad = false; return; }	//BGM読み込み
	IsLoad = true;

}

//デストラクタ
Ranking::~Ranking()
{

}

//初期設定
void Ranking::SetInit()
{
	back->SetInit();	//背景画像初期設定
	for (auto b : bgm) { b->SetInit(DX_PLAYTYPE_LOOP, VOL_DEF); }	//BGM初期設定

}


//ランキング画面の処理
void Ranking::Run()
{

	bgm.front()->Play();			//BGMを流す
	back->Draw(GAME_LEFT, GAME_TOP);//背景描画

	//***************** スコアの描画 ********************
	font.at(HDL_RANK)->Chenge();				//フォント変更
	for (auto d : data) { d->Draw(GameMode); }	//スコア描画
	font.at(HDL_NR)->Chenge();				//フォント変更

	if (Mouse::OnLeftClick())	//左クリックされたら
	{
		bgm.front()->Stop();	//BGMを止める
		NowScene = SCENE_TITLE;	//タイトル画面へ
	}

}
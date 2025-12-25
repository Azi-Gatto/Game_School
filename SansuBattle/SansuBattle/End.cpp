//End.cpp
//エンド画面の処理

//############# ヘッダファイル読み込み ###############
#include "End.hpp"

//############# クラス定義 ################

//コンストラクタ
End::End()
{
	
}

//デストラクタ
End::~End()
{

}

//初期設定
void End::SetInit()
{
	back->SetInit();	//背景画像初期設定
	for (auto b : bgm) { b->SetInit(DX_PLAYTYPE_LOOP, VOL_DEF); }	//BGM初期設定
}


//エンド画面の処理
void End::Run()
{

	bgm.front()->Play();		//BGMを流す

	if (Mouse::OnLeftClick())	//左クリックされたら
	{
		bgm.front()->Stop();	//BGMを止める
		NowScene = SCENE_TITLE;	//タイトル画面へ
	}

	back->Draw(GAME_LEFT, GAME_TOP);//背景描画

}
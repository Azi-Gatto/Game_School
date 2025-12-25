//Load.cpp
//ロード画面のクラス

//############## ヘッダファイル読み込み #################
#include "Load.hpp"

//############## クラス定義 ################

//コンストラクタ
Load::Load()
{
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);	//フォントタイプ変更
	SetFontSize(DEFF_FONT_SIZE);	//フォントサイズ変更
	IsLoad = Animation::CreateList();	//アニメーションリスト作成
}

//デストラクタ
Load::~Load()
{
	Animation::DeleteHandle();	//リストに読み込んだハンドルを削除
}

//初期設定
void Load::SetInit()
{

}

//読み込み画面の処理
void Load::PlayScene()
{

	if (GetASyncLoadNum() == 0)	//非同期で読み込んでいる処理が終わったら
	{

		SetUseASyncLoadFlag(FALSE);	//同期読み込みに設定

		IsGameStart = true;		//ゲームスタートできる
	}

	DrawString(DISCRIPTION_X, DISCRIPTION_Y, DISCRIPTION_TEXT, COLOR_WHITE);	//説明のテキストを描画

	if (IsGameStart)	//ゲームスタートできるなら
	{
		if (Mouse::OnLeftClick())	//左クリックされたら
		{
			SetFontSize(PLAY_FONT_SIZE);	//フォントサイズ変更
			NowScene = SCENE_TITLE;	//タイトル画面へ
		}

		DrawString(GAME_LEFT, GAME_TOP, PUSH_TEXT, COLOR_WHITE);	//プッシュ、のテキストを描画
	}
	else		//できないなら
	{
		DrawString(GAME_LEFT, GAME_TOP, LOAD_TEXT, COLOR_WHITE);	//読み込み中のテキストを描画
	}


}

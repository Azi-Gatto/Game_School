//Load.cpp
//ロード画面のクラス

//############## ヘッダファイル読み込み #################
#include "Load.hpp"

//############## クラス定義 ################

bool Load::LoadEnd = false;	//読み込みが終わったか

//コンストラクタ
Load::Load()
{
	//メンバー初期化
	IsGameStart = false;	//ゲームスタートできるか

	IsLoad = true;

}

//デストラクタ
Load::~Load(){}

//初期設定
void Load::SetInit(){}

//読み込み画面の処理
void Load::Run()
{
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
		LoadEnd = true;				//読み込み終了
		IsGameStart = true;			//ゲームスタートできる

		//説明メッセージを描画
		//DrawStringToHandle(TEXT_DISCRIPTION_X, TEXT_DISCRIPTION_Y, TEXT_DISCRIPTION, COLOR_WHITE, Font::GetNowHandle());
		DrawString(TEXT_DISCRIPTION_X, TEXT_DISCRIPTION_Y, TEXT_DISCRIPTION, COLOR_WHITE);
	}
	else		//読み込み中は
	{
		//読み込みメッセージを描画
		//DrawStringToHandle(TEXT_DISCRIPTION_X, TEXT_DISCRIPTION_Y, TEXT_LOAD_MSG, COLOR_WHITE, Font::GetNowHandle());
		DrawString(TEXT_DISCRIPTION_X, TEXT_DISCRIPTION_Y, TEXT_LOAD_MSG, COLOR_WHITE);

	}


}

//読み込みが終わったか取得
bool Load::IsLoadEnd()
{
	return LoadEnd;
}

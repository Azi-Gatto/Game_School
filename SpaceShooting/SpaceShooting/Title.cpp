//Title.cpp
//タイトル画面の処理

//############# ヘッダファイル読み込み ##################
#include "Title.hpp"

//############ クラス定義 ################

//コンストラクタ
Title::Title()
{
	if (!back->Load(IMG_DIR_BACK, IMG_NAME_TITLE)) { IsLoad = false; return; }	//背景画像読み込み
	if (!bgm->Load(MUSIC_DIR_BGM, BGM_NAME_TITLE)) { IsLoad = false; return; }	//BGM読み込み

	//ボタンの画像
	bt_img.push_back(new Image(BT_IMG_DIR, BT_START_IMG_NAME));	//ボタン（スタート）追加
	bt_img.push_back(new Image(BT_IMG_DIR, BT_END_IMG_NAME));	//ボタン（エンド）追加
	for (auto i : bt_img)
	{
		if (!i->GetIsLoad()) { IsLoad = false; return; }	//読み込み失敗
	}

	//ボタン
	button.push_back(new Button(bt_img.at(BT_START)));	//ボタン（スタート）生成
	button.push_back(new Button(bt_img.at(BT_END)));	//ボタン（エンド）生成

	IsLoad = true;	//読み込み成功
}

//デストラクタ
Title::~Title()
{

}

//初期設定
void Title::SetInit()
{
	back->SetInit();	//背景画像初期設定
	bgm->SetInit(DX_PLAYTYPE_LOOP, 30);		//BGM初期設定

	button.at(BT_START)->SetInit(BT_START_X, BT_START_Y);	//スタートボタン設定
	button.at(BT_END)->SetInit(BT_END_X, BT_END_Y);			//エンドボタン設定
}

//タイトル画面の処理
void Title::PlayScene()
{
	bgm->Play();	//BGMを流す

	back->Draw(GAME_LEFT, GAME_TOP);	//背景描画

	//ボタン処理
	ButtonFunc();

}

//ボタン毎の処理
void Title::ButtonFunc()
{

	int cnt = 0;	//カウント用
	for (auto b : button)
	{
		b->UpDate();//更新
		b->Draw();	//ボタン描画
		if (b->OnClick())	//ボタンをクリックされたら
		{
			//ボタン毎の処理を設定
			switch (cnt)	//要素番号ごと
			{

			case BT_START: //start

				//クリックされた時のイベント処理を作成
				b->Event([this]
					{
						bgm->Stop();			//BGMを止める
						NowScene = SCENE_PLAY;	//プレイ画面へ
					});

				break;	//start

			case BT_END:	//end

				//クリックされた時のイベント処理を作成
				b->Event([this]
					{
						GameEnd = true;			//ゲーム終了
					});

				break;	//end

			default:
				break;
			}
		}
		++cnt;	//カウントアップ
	}

}
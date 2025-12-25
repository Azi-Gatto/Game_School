//main.cpp

//#################### ヘッダファイル読み込み #######################
#include "main.hpp"
#include "Global.hpp"
#include "Fps.hpp"
#include "Scene.hpp"
#include "Load.hpp"
#include "Title.hpp"
#include "Play.hpp"
#include "End.hpp"

using std::vector;
//########## グローバルオブジェクト ##########
Fps* fps = new Fps(GAME_FPS_SPEED);				//fps生成
vector<Scene*> scene;	//シーン

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//タイトルバーあり

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//タイトルの文字

	SetWindowIconID(GAME_ICON_ID);								//アイコン変更

	SetUseASyncLoadFlag(TRUE);									//同期読み込みに設定

	SetAlwaysRunFlag(TRUE);										//非アクティブに設定

	if (DxLib_Init() == -1) { return -1; }						//ＤＸライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);								//Draw系関数は裏画面に描画

	AddScene();	//シーンを追加

	//ゲームのメインループ
	while (GameLoop())
	{
		/*
		ループ内で異常が発生するまで無限ループ
		ゲーム終了やエラー等が発生したらループ終了
		*/
	}


	Delete_Class();			//使用したクラスを破棄

	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//ゲームのループ
bool GameLoop()
{
	if (ProcessMessage() != 0) { return false; }	//メッセージ処理の結果がエラーのとき、強制終了

	if (ClearDrawScreen() != 0) { return false; }	//画面を消去できなかったとき、強制終了

	Mouse::ClickUpDate();	//マウスの状態を更新する

	fps->Update();		//FPSの処理[更新]

	if (Scene::IsGameEnd()) { return false; }	//ゲーム終了

	//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼

	if (Scene::GetIsGameStart())	//ゲームスタートできるとき
	{
		static bool IsInit = false;	//初期設定をしたか
		if (!IsInit)	//初期設定をしていなかったら
		{
			for (auto s : scene)
			{
				if (!s->GetIsLoad()) { return false; }	//読み込み失敗時
				s->SetInit();	//初期設定
			}
			IsInit = true;		//初期設定終了
		}

	}

	scene.at(Scene::GetNowScene())->PlayScene();	//各シーンの処理

	//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

	ScreenFlip();			//モニタのリフレッシュレートの速さで裏画面を再描画

	fps->Wait();			//FPSの処理[待つ]

	return true;			//正常

}

//シーン追加
void AddScene()
{
	scene.push_back(new Load());	//ロード画面追加
	scene.push_back(new Title());	//タイトル画面追加
	scene.push_back(new Play());	//プレイ画面追加
	scene.push_back(new End());		//エンド画面追加
}

//ゲーム内で使用したクラスを削除する処理
void Delete_Class()
{

	delete fps;				//fps破棄

	//scene関係
	for (auto s : scene)
	{
		delete s;			//scene破棄
	}

	return;
}

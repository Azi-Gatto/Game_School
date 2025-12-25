//Select.cpp
//選択の処理

//############# ヘッダファイル読み込み ###############
#include "Select.hpp"

//############# クラス定義 ################

//コンストラクタ
Select::Select()
{
	//画像関係
	if (!back->Load(IMG_DIR_BACK, IMG_NAME_SELECT)) { IsLoad = false; return; }	//背景画像読み込み

	//BGM
	if (!bgm.front()->Load(MUSIC_DIR_BGM, BGM_NAME_SELECT)) { IsLoad = false; return; }	//BGM読み込み

	//**************************** ボタン ***************************
	//ボタンの画像を読み込み
	//モード
	mode_img.push_back(new Image(BT_IMG_DIR, BT_SUM_IMG_NAME));//+
	mode_img.push_back(new Image(BT_IMG_DIR, BT_DIF_IMG_NAME));//-
	mode_img.push_back(new Image(BT_IMG_DIR, BT_PRO_IMG_NAME));//*
	mode_img.push_back(new Image(BT_IMG_DIR, BT_DEA_IMG_NAME));// /
	mode_img.push_back(new Image(BT_IMG_DIR, BT_SUM_DIF_IMG_NAME));//+-
	mode_img.push_back(new Image(BT_IMG_DIR, BT_PRO_DEA_IMG_NAME));//*/
	mode_img.push_back(new Image(BT_IMG_DIR, BT_SUM_PRO_IMG_NAME));//+*
	mode_img.push_back(new Image(BT_IMG_DIR, BT_SUM_DEA_IMG_NAME));//+/
	mode_img.push_back(new Image(BT_IMG_DIR, BT_DIF_PRO_IMG_NAME));//-*
	mode_img.push_back(new Image(BT_IMG_DIR, BT_SUM_DIF_PRO_IMG_NAME));//+-*
	mode_img.push_back(new Image(BT_IMG_DIR, BT_SUM_DIF_DEA_IMG_NAME));//+-/
	mode_img.push_back(new Image(BT_IMG_DIR, BT_ALL_IMG_NAME));//all

	for (auto i : mode_img) { 
		if (!i->GetIsLoad())
		{
			IsLoad = false;
			return;
		}
	}	//読み込み成功したか

	//レベル
	level_img.push_back(new Image(BT_IMG_DIR, BT_EASY_IMG_NAME));//簡単
	level_img.push_back(new Image(BT_IMG_DIR, BT_NORMAL_IMG_NAME));//普通
	level_img.push_back(new Image(BT_IMG_DIR, BT_HARD_IMG_NAME));//難しい

	for (auto i : level_img) {
		if (!i->GetIsLoad())
		{
			IsLoad = false;
			return;
		}
	}	//読み込み成功したか

	//ボタン作成
	for (auto i : mode_img){ mode.push_back(new Button(i)); }		//モード
	for (auto i : level_img) { level.push_back(new Button(i)); }	//レベル

	next = new Button(new Image(BT_IMG_DIR, BT_NEXT_IMG_NAME));		//次のページへ移動するボタン
	prev = new Button(new Image(BT_IMG_DIR, BT_PREV_IMG_NAME));		//前のページへ移動するボタン
	cancel = new Button(new Image(BT_IMG_DIR, BT_BACK_IMG_NAME));	//戻るボタン


}

//デストラクタ
Select::~Select()
{
	
	//ボタンをグループ毎破棄
	delete mode_group;	
	//vectorの開放
	vector<Button*> v;
	v.swap(mode);

	//ボタンをグループ毎破棄
	delete level_group;	
	//vectorの開放
	vector<Button*> v2;
	v2.swap(level);

	//ボタンの画像は、ボタンの破棄と一緒に破棄されるため
	//vectorの開放のみ行う
	vector<Image*> v3;
	v3.swap(level_img);
	vector<Image*> v4;
	v4.swap(level_img);

	delete next;	//nextボタン破棄
	delete prev;	//prevボタン破棄
	delete cancel;	//cancelボタン破棄


}

//初期設定
void Select::SetInit()
{
	back->SetInit();	//背景画像初期設定
	for (auto b : bgm) { b->SetInit(DX_PLAYTYPE_LOOP, VOL_DEF); }	//BGM初期設定

	//**************** ボタン ******************
	for (auto b : mode) { b->SetInit(20, 20); }
	for (auto b : level) { b->SetInit(20, 20); }
	next->SetInit();	//初期設定
	next->SetRect(GAME_WIDTH - next->GetWidth(), GAME_HEIGHT / 2 - next->GetHeight() / 2);	//位置設定
	prev->SetInit();	//初期設定
	prev->SetRect(GAME_LEFT, GAME_HEIGHT / 2 - next->GetHeight() / 2);	//位置設定
	cancel->SetInit();	//初期設定
	cancel->SetRect(GAME_LEFT, GAME_TOP);	//位置設定

	//ボタンをグループに登録
	mode_group = new Group(mode, BT_MODE_DRAW_X, BT_MODE_DRAW_Y, BT_MODE_INTERVAL_SIDE, BT_MODE_INTERVAL_VERTICAL);
	level_group = new Group(level, BT_LEVEL_DRAW_X, BT_LEVEL_DRAW_Y, BT_LEVEL_INTERVAL_SIDE, BT_LEVEL_INTERVAL_VERTICAL);

}

//選択画面の処理
void Select::Run()
{

	Start();	//シーンが変わるごとに1回だけ行う処理

	bgm.front()->Play();		//BGMを流す
	back->Draw(GAME_LEFT, GAME_TOP);//背景描画

	if (mode_group->GetIsSelect())	//モードの選択をしたら
	{
		level_group->Draw();	//レベル描画
		level_group->Clik();	//レベルのクリック処理
		cancel->Draw();			//キャンセルボタンの描画
		if (cancel->OnClick())	//キャンセルボタンを押したら
		{
			//イベント登録、実行
			cancel->Event([this]
				{
					mode_group->Reset();	//モードの選択リセット
				});
		}
	}
	else		//モードの選択をしていなければ
	{
		mode_group->Draw();	//モード描画
		mode_group->Clik();	//モードクリック処理
		//前後のページへ移動するためのボタン
		if (mode_group->CheckIsNextPage())	//次のページがあるとき
		{
			next->Draw();	//次のページへ移動するためのボタンを描画
			if (next->OnClick())	//クリックされたら
			{
				//イベントを登録し、実行
				next->Event([this]
					{
						mode_group->NextPage();	//次のページへ
					});
			}
		}
		if (mode_group->CheckIsPrevPage())	//前のページがあるとき
		{
			prev->Draw();	//前のページへ移動するためのボタンを描画
			if (prev->OnClick())	//クリックされたら
			{
				//イベントを登録し、実行
				prev->Event([this]
					{
						mode_group->PrevPage();	//前のページへ
					});
			}
		}
	}



	if (level_group->GetIsSelect())//レベルの選択をしたら
	{
		GameMode = mode_group->GetSelctNum();	//選択したモードを設定
		GameLevel = level_group->GetSelctNum();	//選択したレベルを設定
		bgm.front()->Stop();					//BGMを止める
		start = false;							//startフラグリセット
		NowScene = SCENE_PLAY;					//プレイ画面へ
	}

}

//シーンが変わるごとに1回だけ行う処理
void Select::Start()
{

	if (!start)	//処理を行っていなければ
	{
		GameMode = -1;			//ゲームモードリセット
		GameLevel = -1;			//ゲームレベルリセット
		mode_group->Reset();	//ゲームモードの選択状態リセット
		level_group->Reset();	//ゲームレベルの選択状態リセット
		start = true;	//処理を行った

	}


}
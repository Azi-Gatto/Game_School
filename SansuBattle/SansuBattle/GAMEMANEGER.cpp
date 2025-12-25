//GameManeger.cpp
//ゲームのシステムを管理するクラス

//############### ヘッダファイル読み込み ################
#include "GameManeger.hpp"

//############### クラス定義 ################

//コンストラクタ
GameManeger::GameManeger()
{
	//オブジェクトの生成
	fps = new Fps(GAME_FPS_SPEED);	//FPSクラスのオブジェクトを生成
	keydown = new KeyDown();			//KEYDOWNクラスのオブジェクトを生成

	//メンバー変数初期化
	NowScene = (int)SCENE_LOAD;		//最初のシーンは、ロード画面
	IsLoad = false;					//読み込み、未完了
	GameMode = -1;					//ゲームモード初期化
	GameLevel = -1;					//ゲームレベル初期化
	GameEndFlg = false;				//ゲーム終了フラグ初期化
	return;

}

//デストラクタ
GameManeger::~GameManeger()
{
	//オブジェクトの破棄
	delete fps;				//fps破棄
	delete keydown;			//keydown破棄
	delete select_gamemode;	//level_select破棄
	delete select_level;	//stage_select破棄
	delete player;			//player破棄
	delete gamelimittime;	//gamelimittime破棄
	delete save;			//save破棄
	delete question;		//question破棄
	delete score;			//score破棄
	delete select_start;	//select_start破棄

	//敵関係
	for (auto e : enemy)
	{
		delete e;	//enemy破棄
	}
	vector<Enemy*> v2;		//空のvectorを作成する
	enemy.swap(v2);			//空と中身を入れ替える

	//フォント関係
	Font::ReleaseFont();	//読み込んだフォントを開放
	for (auto font : this->font)
	{
		delete font;	//font破棄
	}
	vector<Font*> v4;		//空のvectorを作成する
	font.swap(v4);			//空と中身を入れ替える

	//音楽関係
	//BGM
	for (auto bgm : this->bgm)
	{
		delete bgm;		//bgm破棄
	}
	vector<Music*> v5;		//空のvectorを作成する
	bgm.swap(v5);			//空と中身を入れ替える

	//プレイ画面のBGM
	for (auto bgm : bgm_play)
	{
		delete bgm;		//bgm_play破棄
	}
	vector<Music*> v6;		//空のvectorを作成する
	bgm_play.swap(v6);		//空と中身を入れ替える

	//プレイ画面のSE
	for (auto s : play_se)
	{
		delete s;	//play_se破棄
	}
	vector<Music*> v7;
	play_se.swap(v7);

	//エフェクト関係
	for (auto effect : effect_atk)
	{
		delete effect;	//effect_atk破棄
	}
	vector<Effect*> v8;		//空のvectorを作成する
	effect_atk.swap(v8);	//空と中身を入れ替える

	//エフェクトSE
	//オブジェクトの破棄は、エフェクトクラスを破棄した時に同時に破棄されるので、
	//vectorの解放だけ行う
	vector<Music*> v9;		//空のvectorを作成する
	effect_se.swap(v9);		//空と中身を入れ替える

	//背景画像
	for (auto img : back)
	{
		delete img;
	}
	vector<Image*> v10;		//空のvector
	back.swap(v10);			//空と交換

	//選択肢画像
	//オブジェクトの破棄は、選択肢クラスを破棄した時に同時に破棄されるので、
	//vectorの解放だけ行う
	vector<Image*> v11;			//空のvector
	gamemode_img.swap(v11);		//空と交換
	vector<Image*> v12;			//空のvector
	gamelevel_img.swap(v12);	//空と交換
	vector<Image*> v13;			//空のvector
	start_img.swap(v13);		//空と交換

}

//ゲーム内で使用するデータの読み込み処理
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool GameManeger::Load()
{

	//フォント関係
	if (Font::LoadFont(FONT_DIR, FONT_FILE_NAME, FONT_NAME) == false) { return false; }	//フォントを読み込み
	font.push_back(new Font(FONT_NAME_KOKUBAN, DEFAULT_FONTSIZE, FONT_BOLD_DEFAULT, DX_FONTTYPE_ANTIALIASING));		//フォントを管理するオブジェクトを生成
	font.push_back(new Font(FONT_NAME_KOKUBAN, FONTSIZE_MINI, FONT_BOLD_DEFAULT, DX_FONTTYPE_ANTIALIASING));		//こくばんフォント（ミニサイズ）作成
	font.push_back(new Font(FONT_NAME_KOKUBAN, FONTSIZE_DRAW_RANKING, FONT_BOLD_DEFAULT, DX_FONTTYPE_ANTIALIASING));//こくばんフォント（ランキングサイズ）作成
	for (auto f : font)
	{
		if (!f->GetIsCreate()) { return false; }	//読み込み失敗
	}

	//時間関係
	gamelimittime = new Time(GAME_LIMIT_TIME);		//ゲームの制限時間を管理するオブジェクトを生成

	//画像関係
	//背景画像
	back.push_back(new Image(IMG_DIR_BACK, IMG_NAME_TITLE));	//背景（タイトル画面）を生成
	back.push_back(new Image(IMG_DIR_BACK, IMG_NAME_PLAY));		//背景（プレイ画面）を生成
	back.push_back(new Image(IMG_DIR_BACK, IMG_NAME_SELECT));	//背景（選択画面）を生成
	back.push_back(new Image(IMG_DIR_BACK, IMG_NAME_SCORE));	//背景（選択画面）を生成
	back.push_back(new Image(IMG_DIR_BACK, IMG_NAME_END));		//背景（エンド画面）を生成
	for (auto img : back)
	{
		if (img->GetIsLoad() == false) { return false; }	//読み込み失敗
	}

	//選択肢関係
	//難易度の選択肢
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_SUM));			//ゲームモード選択肢の画像生成(足し算)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_DIFFERENCE));	//ゲームモード選択肢の画像生成(引き算)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_PRODUCT));		//ゲームモード選択肢の画像生成(掛け算)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_DEALER));		//ゲームモード選択肢の画像生成(割り算)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_SUM_DIFF));	//ゲームモード選択肢の画像生成(足し算引き算)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_PRO_DEA));		//ゲームモード選択肢の画像生成(掛け算割り算)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_SUM_PRO));		//ゲームモード選択肢の画像生成(+*)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_SUM_DEA));		//ゲームモード選択肢の画像生成(+/)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_DIF_PRO));		//ゲームモード選択肢の画像生成(-*)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_SUM_DIF_PRO));	//ゲームモード選択肢の画像生成(+-*)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_SUM_DIF_DEA));	//ゲームモード選択肢の画像生成(+-/)
	gamemode_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_ALL));			//ゲームモード選択肢の画像生成(+-*/)

	for (auto img : gamemode_img)
	{
		if (!img->GetIsLoad()) { return false; }	//読み込み失敗
	}
	select_gamemode = new Select(gamemode_img);	//ゲームモードの選択肢生成

	//ステージの選択肢
	gamelevel_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECTLEVEL_EASY));		//ゲームレベル選択肢の画像生成(簡単)
	gamelevel_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECTLEVEL_NORMAL));	//ゲームレベル選択肢の画像生成(普通)
	gamelevel_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECTLEVEL_HARD));		//ゲームレベル選択肢の画像生成(難しい)
	for (auto img : gamelevel_img)
	{
		if (!img->GetIsLoad()) { return false; }	//読み込み失敗
	}
	select_level = new Select(gamelevel_img);	//ゲームレベルの選択肢生成

	//スタートの選択肢
	start_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_START));		//スタートの画像
	start_img.push_back(new Image(SELECT_IMG_DIR, IMG_NAME_SELECT_END));		//エンドの画像
	for (auto img : start_img)
	{
		if (!img->GetIsLoad()) { return false; }	//読み込み失敗
	}
	select_start = new Select(start_img);			//スタートの選択肢生成

	//プレイヤー関係
	player = new Player();		//プレイヤーを管理するオブジェクトを生成

	//敵関係
	enemy.push_back(new Enemy(IMG_DIR_ENEMY, IMG_NAME_ENEMY_FIRST));	//敵を管理するオブジェクトを生成(1体目)
	enemy.push_back(new Enemy(IMG_DIR_ENEMY, IMG_NAME_ENEMY_SECOND));	//敵を管理するオブジェクトを生成(2体目)
	enemy.push_back(new Enemy(IMG_DIR_ENEMY, IMG_NAME_ENEMY_THIRD));	//敵を管理するオブジェクトを生成(3体目)
	for (int i = 0; i < enemy.size(); ++i)	//敵の数だけ
	{
		if (enemy.at(i)->GetIsLoad() == false) { return false; }		//読み込み失敗
	}

	//エフェクト関係
	effect_se.push_back(new Music(MUSIC_DIR_EFFECT, SE_NAME_EFFECT_ATK));	//エフェクトの効果音作成
	for (auto se : effect_se)
	{
		if (se->GetIsLoad() == false) { return false; }	//読み込み失敗
	}
	effect_atk.push_back(new Effect(EFFECT_DIR, EFFECT_NAME_ATACK, EFFECT_ATACK_ALL_CNT, EFFECT_ATACK_YOKO_CNT, EFFECT_ATACK_TATE_CNT,
		EFFECT_ATACK_WIDTH, EFFECT_ATACK_HEIGHT, EFFECT_ATACK_SPEED, false,effect_se.at((int)SE_EFFECT_ATACK)));	//攻撃エフェクトを管理するオブジェクトを生成
	for (auto effect : effect_atk)
	{
		if (effect->GetIsLoad() == false) { return false; }	//読み込み失敗
	}

	//音楽関係
	//BGM
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_TITLE_BGM));					//BGMを管理するオブジェクトを生成
	bgm.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_SELECT_BGM));					//選択肢画面のBGM追加
	for (auto bgm : this->bgm)
	{
		if (bgm->GetIsLoad() == false) { return false; }	//読み込み失敗
		bgm->SetInit(DX_PLAYTYPE_LOOP, 30);					//初期設定
	}
	//プレイ画面のBGM
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_BGM));			//BGM(プレイ画面)を管理するオブジェクトを生成
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_DIFF_BGM));			//プレイ画面（引き算）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_PRO_BGM));			//プレイ画面（掛け算）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_DEA_BGM));			//プレイ画面（割り算）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_DIF_BGM));		//プレイ画面（足し算、引き算）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_PRO_DEA_BGM));		//プレイ画面（掛け算、割り算）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_PRO_BGM));		//プレイ画面（+*）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_DEA_BGM));		//プレイ画面（+/）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_DIF_PRO_BGM));		//プレイ画面（-*）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_DIF_PRO_BGM));	//プレイ画面（+-*）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_SUM_DIF_DEA_BGM));	//プレイ画面（+-/）のBGM追加
	bgm_play.push_back(new Music(MUSIC_DIR_BGM, BGM_NAME_PLAY_ALL_BGM));			//プレイ画面（+-*/）のBGM追加
	for (auto bgm : bgm_play)
	{
		if (bgm->GetIsLoad() == false) { return false; }	//読み込み失敗
		bgm->SetInit(DX_PLAYTYPE_LOOP, 30);					//初期設定
	}

	//効果音（プレイ画面）
	play_se.push_back(new Music(MUSIC_DIR_SE, SE_NAME_FALSE));	//不正解の効果音追加
	play_se.push_back(new Music(MUSIC_DIR_SE, SE_NAME_DAMEGE));	//ダメージの効果音追加
	for (auto s : play_se)
	{
		if (!s->GetIsLoad()) { return false; }	//読み込み失敗
		s->SetInit(DX_PLAYTYPE_BACK, 30);		//初期設定
	}

	//問題関係
	question = new Question();	//問題を管理するオブジェクトを生成

	//スコア関係
	score = new Score();		//スコアを管理するオブジェクトを生成

	//セーブデータ関係
	save = new SaveData();			//セーブデータを管理するオブジェクトを生成
	return true;	//読み込み成功
}

//ゲームのメインループ
/*
戻り値：true：正常
戻り値：false：エラー、強制終了
*/
bool GameManeger::GameMainLoop()
{
	if (ProcessMessage() != 0) { return false; }	//メッセージ処理の結果がエラーのとき、強制終了

	if (ClearDrawScreen() != 0) { return false; }	//画面を消去できなかったとき、強制終了

	keydown->KeyDownUpdate();	//キーの入力状態を更新する

	fps->Update();		//FPSの処理[更新]

	if (GameEndFlg) { return false; }		//ゲーム終了フラグが立ったら、強制終了

	//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼

	ProcesScene();		//各シーンの処理

	//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

	//this->fps->Draw(0, 0);		//FPS描画

	ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

	fps->Wait();			//FPSの処理[待つ]

	return true;				//正常

}

//各シーンの処理
void GameManeger::ProcesScene()
{
	switch (NowScene)		//現在のシーンの描画処理を実行
	{

	case (int)SCENE_LOAD:	//ロード画面のとき

		Scene_Load();			//ロード画面の処理

		Draw_Scene_Load();	//ロード画面の描画処理

		break;				//ロード画面のときここまで

	case (int)SCENE_TITLE:	//タイトル画面のとき

		Scene_Title();		//処理

		Draw_Scene_Title();	//描画

		break;				//タイトル画面のときここまで

	case (int)SCENE_SELECT_MODE:	//難易度選択画面のとき

		Scene_ChoiseGameMode();		//処理

		Draw_Scene_ChoiseGameMode();	//描画

		break;				//難易度選択画面のときここまで

	case (int)SCENE_SELECT_LEVEL:	//ステージ選択画面のとき

		Scene_ChoiseLevel();		//処理

		Draw_Scene_ChoiseLevel();	//描画

		break;				//ステージ選択画面のときここまで

	case (int)SCENE_PLAY:	//プレイ画面のとき

		Scene_Play();			//処理

		Draw_Scene_Play();	//描画

		break;				//プレイ画面のときここまで

	case (int)SCENE_DRAWSCORE:	//スコア表示画面のとき

		Scene_DrawScore();		//処理

		Draw_SceneDrawScore();	//描画

		break;				//スコア表示画面のときここまで

	default:
		break;
	}

	return;	

}

//初期設定
void GameManeger::SetInit()
{
	NowFontHandle = font.at((int)HANDLE_NR_SIZE)->GetHandle();	//使用するフォントをこくばんフォントに変更

	select_gamemode->SetInit(SELECT_GAMEMODE_DRAW_X, SELECT_GAMEMODE_DRAW_Y,  SELECT_GAMEMODE_INTERVAL_SIDE, SELECT_GAMEMODE_INTERVAL_VERTICAL);	//ゲームモードの選択肢初期設定
	select_level->SetInit(SELECT_LEVEL_DRAW_X, SELECT_LEVEL_DRAW_Y,  SELECT_LEVEL_INTERVAL_SIDE);				//レベルの選択肢初期設定
	select_start->SetInit(START_DRAW_X, START_DRAW_Y, SELECT_START_INTERVAL_SIDE);	//スタートの選択肢の初期設定
	player->SetInit(PLAYER_HP_DRAW_X, PLAYER_HP_DRAW_Y);							//プレイヤー初期設定

	for (auto img : back)
	{
		img->SetInit();	//初期設定
	}

	for (auto effect : effect_atk)
	{
		effect->SetInit();	//初期設定
	}

	for (int i = 0; i < enemy.size(); ++i)
	{
		enemy.at(i)->SetInit(ENEMY_HP_DRAW_X, ENEMY_HP_DRAW_Y);	//敵の初期設定
	}

	return;
}

//***************************** シーン毎の処理 ********************************
//ロード画面の処理
void GameManeger::Scene_Load()
{
	if (IsLoad)	//読み込みが完了していたら
	{
		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
		{
			NowScene = (int)SCENE_TITLE;	//タイトル画面へ
		}
	}
	else		//読み込みが完了していなかったら
	{
		if (GetASyncLoadNum() == 0)	//非同期で読み込んでいる処理が終わったら
		{

			SetUseASyncLoadFlag(FALSE);	//同期読み込みに設定

			SetInit();			//初期設定

			IsLoad = true;		//読み込み完了
		}

	}


	return;		
}

//ロード画面の描画処理
void GameManeger::Draw_Scene_Load()
{

	SetFontSize(DEFAULT_FONTSIZE);	//フォントサイズを大きくする

	if (IsLoad)	//読み込みが完了したら
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, PUSH_TEXT, COLOR_WHITE);
	}
	else		//完了していなければ
	{
		DrawString(TEST_TEXT_X, TEST_TEXT_Y, LOAD_TEXT, COLOR_WHITE);
	}

	return;
}

//タイトル画面の処理
void GameManeger::Scene_Title()
{

	bgm.at((int)BGM_TYPE_TITLE)->Play();		//BGMを再生

	select_start->Operation(keydown);			//選択肢のキー操作

	if (select_start->GetIsChoise())	//選択されたら
	{
		if (select_start->GetChoiseSelectCode() == SELECT_START)	//スタートだったら
		{
			bgm.at(BGM_TYPE_TITLE)->Stop();//再生中の音楽を止める
			select_start->Init();			//初期化
			NowScene = SCENE_SELECT_MODE;	//難易度選択画面へ
		}
		else	//エンドだったら
		{
			GameEndFlg = true;	//ゲーム終了
		}

	}
}

//タイトル画面の描画処理
void GameManeger::Draw_Scene_Title()
{

	back.at((int)TITLE_BACK)->Draw(GAME_LEFT, GAME_TOP);	//背景描画

	select_start->Draw();	//スタートの選択肢描画

}

//ゲームモード選択画面の処理
void GameManeger::Scene_ChoiseGameMode()
{

	bgm.at((int)BGM_TYPE_SELECT)->Play();	//選択画面のBGMを再生

	select_gamemode->Operation(keydown);			//選択肢キー操作

	if (select_gamemode->GetIsChoise())			//選択したら
	{
		GameMode = select_gamemode->GetChoiseSelectCode();		//ゲームレベル設定

		//(読み込み成功時はtrueが返ってくるので、そのまま代入するとゲーム終了してしまうため、反転させている。）
		GameEndFlg = !(save->Load(GameMode));					//セーブデータ読み込み

		select_gamemode->Init();	//ゲームモードの選択肢初期化

		NowScene = (int)SCENE_SELECT_LEVEL;						//ステージ選択画面へ
	}

	return;
}

//ゲームモード選択画面の描画処理
void GameManeger::Draw_Scene_ChoiseGameMode()
{
	back.at((int)SELECT_BACK)->Draw(GAME_LEFT, GAME_TOP);	//背景描画

	select_gamemode->Draw();				//難易度の選択肢描画

	return;
}

//レベル選択画面の処理
void GameManeger::Scene_ChoiseLevel()
{

	select_level->Operation(keydown);		//選択肢キー操作

	if (select_level->GetIsChoise())		//選択したら
	{
		GameLevel = select_level->GetChoiseSelectCode();	//ゲームレベルを設定
		bgm.at((int)BGM_TYPE_SELECT)->Stop();				//再生中のBGMを止める
		for (int i = 0; i < enemy.size(); ++i)	//敵の数分ループ
		{
			enemy.at(i)->Init();			//敵初期化
		}
		player->Init();						//プレイヤー初期化
		score->ResetScore();				//スコアリセット
		select_level->Init();				//レベルの選択肢初期化
		gamelimittime->SetTime();			//制限時間の計測開始
		NowScene = (int)SCENE_PLAY;			//プレイ画面へ
	}
	else if (select_level->GetIsBack())		//戻るとき
	{
		select_level->Init();				//レベルの選択肢初期化
		NowScene = (int)SCENE_SELECT_MODE;	//ゲームモード選択画面へ
	}

	return;
}

//レベル選択画面の描画処理
void GameManeger::Draw_Scene_ChoiseLevel()
{

	back.at((int)SELECT_BACK)->Draw(GAME_LEFT, GAME_TOP);	//背景描画

	select_level->Draw();		//ステージ選択肢描画

	return;
}

//プレイ画面の処理
void GameManeger::Scene_Play()
{

	bgm_play.at(GameMode)->Play();			//プレイ画面のBGMを再生

	gamelimittime->UpdateLimitTime();		//制限時間の更新

	if (!question->GetIsCreate())	//問題を作成していなければ
	{
		question->Create(GameMode, GameLevel);	//問題を作成
	}

	if (question->CheckInputKey(keydown))	//キー入力が完了したら
	{
		if (question->JudgAnser())			//プレイヤーの回答が正解だったら
		{
			effect_atk.at((int)EFFECT_ATACK)->SetIsDraw(true);			//アニメーションの描画を開始する
		}
		else		//不正解だったら
		{
			play_se.at(SE_PLAY_FALSE)->Play();				//不正解の効果音
			gamelimittime->MinusLimitTime(MISS_MINUS_TIME);	//制限時間を減らす
			question->InpReset();							//入力情報リセット
		}

	}

	if (effect_atk.at((int)EFFECT_ATACK)->GetIsDrawEnd())					//アニメーション描画が終わったら
	{
		effect_atk.at((int)EFFECT_ATACK)->SetIsDraw(false);					//アニメーションを描画しない
		effect_atk.at((int)EFFECT_ATACK)->ResetIsAnime();					//アニメーション状態をリセット
		enemy.at(Enemy::GetNowEnemyNum())->SendDamege();					//敵にダメージを与える
		score->CalcScore(GameMode, GameLevel, gamelimittime->GetElapsedTime());//スコア加算
		gamelimittime->SetTime();											//制限時間の再計測
	}

	if (gamelimittime->GetIsLimit())		//制限時間を超えたら
	{
		play_se.at(SE_PLAY_DAMEGE)->Play();	//ダメージの効果音
		player->SendDamege();				//プレイヤーにダメージ
		question->Reset();					//問題をリセット
		gamelimittime->SetTime();			//制限時間の再計測
	}

	if (enemy.at(Enemy::GetNowEnemyNum())->GetHp() <= 0)		//敵のHPが0になったら
	{
		enemy.at(Enemy::GetNowEnemyNum())->SetIsArive(false);	//敵死亡
		if (enemy.at(Enemy::GetNowEnemyNum())->GetFadeEnd())	//フェードアウト終了したら
		{
			Enemy::NextEnemy();	//次の敵へ
		}
	}
	
	if (Enemy::GetNowEnemyNum() >= enemy.size() ||			//敵の数が、最大数を超えたら
		player->GetHp() <= 0)								//プレイヤーのHPが0になったら	
	{
		save->Add(score->GetScore());		//スコアを追加
		save->Sort();						//ソート処理
		save->Save(GameMode);				//結果をセーブ
		bgm_play.at(GameMode)->Stop();		//再生中のBGMを止める
		NowScene = (int)SCENE_DRAWSCORE;	//スコア表示画面へ
	}

}

//プレイ画面の描画処理
void GameManeger::Draw_Scene_Play()
{

	back.at((int)PLAY_BACK)->Draw(GAME_LEFT, GAME_TOP);	//背景描画

	if (Enemy::GetNowEnemyNum() < enemy.size())	//現在の敵が、敵の最大数位内だったら
	{
		enemy.at(Enemy::GetNowEnemyNum())->DrawCenter();	//敵キャラ描画
		enemy.at(Enemy::GetNowEnemyNum())->DrawHp();		//HP描画
	}

	player->DrawHp();				//プレイヤーHP描画

	//問題関係
	NowFontHandle = font.at(HANDLE_MINI_SIZE)->GetHandle();//使用するフォントハンドル変更
	question->DrawQuestion();								//問題文描画
	NowFontHandle = font.at(HANDLE_NR_SIZE)->GetHandle();	//使用するフォントハンドル変更
	question->DrawInputNum();		//入力中の数字を描画

	score->DrawNowScore();	//現在のスコア描画

	gamelimittime->DrawLimitTime(GAME_LIMITTIME_DRAW_X, GAME_LIMITTIME_DRAW_Y);			//制限時間の描画

	effect_atk.at((int)EFFECT_ATACK)->DrawCenter();	//攻撃エフェクト描画

	return;
}

//スコア表示画面の処理
void GameManeger::Scene_DrawScore()
{

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
	{
		NowScene = (int)SCENE_TITLE;	//タイトル画面へ
	}

	return;
}

//スコア表示画面の描画処理
void GameManeger::Draw_SceneDrawScore()
{

	back.at(SCORE_BACK)->Draw(GAME_LEFT, GAME_TOP);	//背景描画

	NowFontHandle = font.at((int)HANDLE_RANK_SIZE)->GetHandle();	//使用するフォントハンドル変更
	save->Draw(GameMode);														//データをランキング表示
	NowFontHandle = font.at((int)HANDLE_NR_SIZE)->GetHandle();	//使用するフォントハンドル変更

	return;
}
